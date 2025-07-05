#include <QApplication>
#include <QTranslator>
#include <QtLogging>
#include <QString>
#include <QLibraryInfo>
#include <QDir>

#include <cstdio>

#include "main_window.h"

using namespace Qt::Literals::StringLiterals;

namespace {
struct LogToFile
{
    LogToFile()
    {
        qSetMessagePattern("[%{time yyyyMMdd h:mm:ss.zzz ttt} "
                           "%{if-debug}DEBUG%{endif}"
                           "%{if-info} INFO%{endif}"
                           "%{if-warning} WARN%{endif}"
                           "%{if-critical} CRIT%{endif}"
                           "%{if-fatal}FATAL%{endif}] "
#if !defined(NDEBUG)
                           "%{file}:%{line} - "
#endif
                           "%{message}"_L1);
        if (QDir().mkpath("log"_L1)) {
            const QString file_name =
                    u"log/%1.txt"_s.arg(QDateTime::currentDateTime().toString("yyyy-MM-dd"_L1));
            f_ = std::fopen(qPrintable(file_name), "a");
            if (f_) {
                o_ = qInstallMessageHandler(&LogToFile::logToFile);
            }
        }
    }
    ~LogToFile()
    {
        if (o_) {
            qInstallMessageHandler(o_);
            o_ = nullptr;
        }
        if (f_) {
            std::fclose(f_);
        }
    }

    static void logToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg)
    {
        if (f_) {
            const QString message = qFormatLogMessage(type, context, msg);
            std::fprintf(f_, "%s\n", qPrintable(message));
            std::fflush(f_);
        }

        if (o_) {
            (*o_)(type, context, msg);
        }
    }

    static inline QtMessageHandler o_;
    static inline std::FILE *f_;
} _init [[maybe_unused]];
} // namespace

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    if (translator.load(QLocale(), "qt"_L1, "_"_L1,
                        QLibraryInfo::path(QLibraryInfo::TranslationsPath))) {
        QCoreApplication::installTranslator(&translator);
    } else {
        qWarning("Failed to load translations");
    }

    MainWindow win;
    win.show();

    return QApplication::exec();
}