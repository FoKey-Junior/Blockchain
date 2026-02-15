#include <QDir>
#include <QFile>
#include <QGuiApplication>
#include <QIcon>
#include <QStringList>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlError>
#include <QStandardPaths>
#include <QTextStream>
#include <QUrl>
#include <QByteArray>
#include <QWindow>
#include <iostream>

#include "gui/app_controller.h"

namespace {
QFile* g_log_file = nullptr;

void write_log_line(const QString& line) {
    if (!g_log_file) {
        return;
    }
    QTextStream ts(g_log_file);
    ts << line << "\n";
    ts.flush();
}

void qt_log_handler(QtMsgType type, const QMessageLogContext&, const QString& msg) {
    QString prefix;
    switch (type) {
        case QtDebugMsg: prefix = "[DEBUG] "; break;
        case QtInfoMsg: prefix = "[INFO] "; break;
        case QtWarningMsg: prefix = "[WARN] "; break;
        case QtCriticalMsg: prefix = "[CRIT] "; break;
        case QtFatalMsg: prefix = "[FATAL] "; break;
    }
    write_log_line(prefix + msg);
    if (type == QtFatalMsg) {
        abort();
    }
}

void init_file_logging() {
    const QString log_dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(log_dir);

    static QFile file(log_dir + "/startup.log");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        return;
    }

    g_log_file = &file;
    qInstallMessageHandler(qt_log_handler);
    write_log_line("[INFO] Starting application");
}

bool load_ui(QQmlApplicationEngine& engine) {
    const QStringList candidates = {
        QStringLiteral("qrc:/qml/Main.qml"),
        QStringLiteral("qrc:/qml/qml/Main.qml"),
        QStringLiteral("qrc:/Main.qml")
    };

    for (const QString& candidate : candidates) {
        engine.load(QUrl(candidate));
        if (!engine.rootObjects().isEmpty()) {
            write_log_line(QString("[INFO] QML loaded from %1").arg(candidate));
            return true;
        }
        write_log_line(QString("[WARN] Failed to load %1").arg(candidate));
    }

    write_log_line("[FATAL] QML root object was not created");
    return false;
}

void sanitize_qt_env_var(const char* key) {
    const QByteArray value = qgetenv(key);
    if (value.isEmpty()) {
        return;
    }
    if (!QDir(QString::fromUtf8(value)).exists()) {
        qunsetenv(key);
        write_log_line(QString("[WARN] Cleared invalid env %1=%2").arg(QString::fromUtf8(key), QString::fromUtf8(value)));
    }
}
} // namespace

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    if (QFile::exists(":/qml/icon.png")) {
        app.setWindowIcon(QIcon(":/qml/icon.png"));
    } else if (QFile::exists(":/qml/assets/icon.png")) {
        app.setWindowIcon(QIcon(":/qml/assets/icon.png"));
    }

    init_file_logging();

    // Чистим только заведомо битые override-пути, валидные пользовательские настройки не трогаем.
    sanitize_qt_env_var("QT_PLUGIN_PATH");
    sanitize_qt_env_var("QT_QPA_PLATFORM_PLUGIN_PATH");
    sanitize_qt_env_var("QML2_IMPORT_PATH");

    AppController controller;
    QQmlApplicationEngine engine;

    QObject::connect(&engine, &QQmlApplicationEngine::warnings, &app,
                     [](const QList<QQmlError>& warnings) {
                         for (const auto& warning : warnings) {
                             const QString line = warning.toString();
                             std::cerr << line.toStdString() << "\n";
                             write_log_line("[QML] " + line);
                         }
                     });

    engine.rootContext()->setContextProperty("appController", &controller);
    if (!load_ui(engine)) {
        // Если основной UI не загрузился, держим процесс живым с аварийным окном.
        auto* fallback_window = new QWindow();
        fallback_window->setTitle(QStringLiteral("BlockchainApp: ошибка загрузки UI"));
        fallback_window->resize(960, 640);
        fallback_window->show();
        write_log_line("[WARN] Fallback window is shown to keep app running");
    }

    return app.exec();
}
