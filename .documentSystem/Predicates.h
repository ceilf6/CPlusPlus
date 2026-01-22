#ifndef PREDICATES_H
#define PREDICATES_H

#include <sstream>
#include "Document.h"

// ===============================
// 通用谓词对象 IsA<Target>
// ===============================
template <class Target>
class IsA
{
public:
    template <class T>
    bool operator()(T *ptr) const
    {
        return dynamic_cast<Target *>(ptr) != nullptr;
    }
};

// ===============================
// 统计文本单词数的谓词
// 仅对 TextDocument 有效
// ===============================
class WordCountPredicate
{
    int totalWords;

public:
    WordCountPredicate() : totalWords(0) {}

    void operator()(Document *doc)
    {
        TextDocument *td = dynamic_cast<TextDocument *>(doc);
        if (!td)
            return;

        std::istringstream iss(td->content());
        std::string word;
        while (iss >> word) // >> 提取到下一个空白字符，即提取一个单词
            ++totalWords;
    }

    int getCount() const { return totalWords; }
};

// ===============================
// 统计 PDF 页数的谓词
// 仅对 PDFDocument 或 EncryptedPDFDocument 有效
// ===============================
class PageCountPredicate
{
    int totalPages;

public:
    PageCountPredicate() : totalPages(0) {}

    void operator()(Document *doc)
    {
        PDFDocument *pdf = dynamic_cast<PDFDocument *>(doc);
        EncryptedPDFDocument *epdf = dynamic_cast<EncryptedPDFDocument *>(doc);
        if (pdf)
            totalPages += pdf->getPages().size();
        else if (epdf)
            totalPages += epdf->getPages().size();
    }

    int getCount() const { return totalPages; }
};

#endif
