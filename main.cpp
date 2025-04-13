#include "main_window.h"

#include <QApplication>
#include <QTranslator>
#include <QStringLiteral>
#include <QtLogging>
#include <QString>
#include <cstdio>

using namespace Qt::Literals::StringLiterals;

struct LogToFile
{
    LogToFile()
    {
        qSetMessagePattern("[%{time yyyyMMdd h:mm:ss.zzz ttt} "
                           "%{if-debug}D%{endif}%{if-info}I%{endif}%{if-warning}W%{endif}%{if-"
                           "critical}C%{endif}%{if-fatal}F%{endif}] "
#if !defined(NDEBUG)
                           "%{file}:%{line} - "
#endif
                           "%{message}"_L1);
        f_ = std::fopen("log.txt", "a");
        o_ = qInstallMessageHandler(&LogToFile::logToFile);
    }
    ~LogToFile()
    {
        qInstallMessageHandler(o_);
        o_ = nullptr;
        std::fclose(f_);
    }

    static void logToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg)
    {
        const QString message = qFormatLogMessage(type, context, msg);
        std::fprintf(f_, "%s\n", qPrintable(message));
        std::fflush(f_);

        if (o_)
            (*o_)(type, context, msg);
    }

    static inline QtMessageHandler o_;
    static inline std::FILE *f_;
} _init;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator t;
    if (t.load(QLocale(), "qt"_L1, "_"_L1, "../translations"_L1)) {
        app.installTranslator(&t);
    } else {
        qWarning("Error when loading translator");
    }

    MainWindow win;
    win.show();

    return app.exec();
}
