#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>
#include <ostream>

/* ===============================
 * 抽象基类：Document
 * =============================== */
class Document {
protected:
    std::string title;

public:
    Document(const std::string& t) : title(t) {}
    virtual ~Document() {}

    virtual std::string content() const = 0;

    const std::string& getTitle() const { return title; }
};

/* ===============================
 * TextDocument
 * =============================== */
class TextDocument : public Document {
    std::string text;

public:
    TextDocument(const std::string& t, const std::string& txt)
        : Document(t), text(txt) {}

    std::string content() const override {
        return text;
    }
};

/* ===============================
 * PDFDocument
 * =============================== */
class PDFDocument : public Document {
protected:
    std::vector<std::string> pages;

public:
    PDFDocument(const std::string& t,
                const std::vector<std::string>& p)
        : Document(t), pages(p) {}

    std::string content() const override {
        std::string result;
        for (std::size_t i = 0; i < pages.size(); ++i) {
            result += "Page ";
            result += std::to_string(i + 1);
            result += ": ";
            result += pages[i];
            result += "; ";
        }
        return result;
    }

    std::size_t pageCount() const {
        return pages.size();
    }

    std::vector<std::string>& getPages() {
        return pages;
    }

    const std::vector<std::string>& getPages() const {
        return pages;
    }
};

/* ===============================
 * EncryptedPDFDocument
 * =============================== */
class EncryptedPDFDocument : public PDFDocument {
public:
    EncryptedPDFDocument(const std::string& t,
                         const std::vector<std::string>& p)
        : PDFDocument(t, p) {}

    std::string content() const override {
        return "[ENCRYPTED PDF CONTENT]";
    }

    // 继承 getPages()，仍然可以统计页数
    using PDFDocument::getPages;
};

#endif
