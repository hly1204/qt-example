#include <QApplication>
#include <QTranslator>
#include <QtLogging>
#include <QString>
#include <QLibraryInfo>

#include <cstdio>

#include "main_window.h"

using namespace Qt::Literals::StringLiterals;

namespace {

struct LogToFile
{
    LogToFile()
    {
        qSetMessagePattern("[%{time yyyyMMdd h:mm:ss.zzz ttt} "
                           "%{if-debug}D%{endif}%{if-info}I%{endif}%{if-warning}W%{endif}"
                           "%{if-critical}C%{endif}%{if-fatal}F%{endif}] "
#if !defined(NDEBUG)
                           "%{file}:%{line} - "
#endif
                           "%{message}"_L1);
        // Note that it depends on the working directory
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

        if (o_) {
            (*o_)(type, context, msg);
        }
    }

    static inline QtMessageHandler o_;
    static inline std::FILE *f_;
} [[maybe_unused]] _init;

} // namespace

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator t;
    if (t.load(QLocale(), "qt"_L1, "_"_L1, QLibraryInfo::path(QLibraryInfo::TranslationsPath))) {
        QCoreApplication::installTranslator(&t);
    } else {
        qWarning("Failed to load translator");
    }

    MainWindow win;
    win.show();

    return QApplication::exec();
}