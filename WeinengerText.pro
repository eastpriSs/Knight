QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Analyzer.cpp \
    AnalyzerApraam.cpp \
    AnalyzerC.cpp \
    ApraamTranslatorLexer.cpp \
    ApraamTranslatorParser.cpp \
    CodeEditor.cpp \
    ConsoleOutput.cpp \
    LanguageList.cpp \
    Lexer.cpp \
    LexerC.cpp \
    MainWindow.cpp \
    Parser.cpp \
    SettingMenuSendAction.cpp \
    SyntaxHighlighter.cpp \
    Token.cpp \
    main.cpp

HEADERS += \
    Analyzer.h \
    AnalyzerApraam.h \
    AnalyzerC.h \
    ApraamTranslatorLexer.h \
    ApraamTranslatorParser.h \
    CodeEditor.h \
    ConsoleOutput.h \
    LanguageList.h \
    Lexer.h \
    LexerC.h \
    MainWindow.h \
    Parser.h \
    SettingMenuSendAction.h \
    SyntaxHighlighter.h \
    Token.h

FORMS += \
    ConsoleOutput.ui \
    MainWindow.ui \
    SettingMenuSendAction.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
