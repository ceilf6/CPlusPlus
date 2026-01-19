#ifndef TRANSFORMERS_H
#define TRANSFORMERS_H

#include "Document.h"
#include <algorithm>
#include <sstream>

/* ========= 工具函数 ========= */

// 不需要掌握
std::string toUpper(const std::string& s) {
    std::string r = s;
    for (std::string::iterator it = r.begin(); it != r.end(); ++it) {
        if (*it >= 'a' && *it <= 'z') {
            *it = *it - 'a' + 'A';
        }
    }
    return r;
}

// 不需要掌握
std::string reverseWords(const std::string& s) {
    std::istringstream iss(s);
    std::ostringstream oss;
    std::string word;

    bool first = true;
    while (iss >> word) {
        std::reverse(word.begin(), word.end());
        if (!first) oss << " ";
        oss << word;
        first = false;
    }
    return oss.str();
}

/* ============================================================
 * Transformer 0：IdentityTransformer
 * 任意 Document → 原始 content()
 * ============================================================ */

class IdentityTransformer {
public:
    std::string operator()(Document* doc) const {
        if (!doc) return "";
        return doc->content();
    }
};

/* ============================================================
 * Transformer 1：大写（仅 TextDocument）
 * ============================================================ */

class UppercaseTransformer {
public:
    std::string operator()(Document* doc) const {
        TextDocument* td = dynamic_cast<TextDocument*>(doc);
        if (!td) return "NOT A TEXT FILE";
        return toUpper(td->content());
    }
};

/* ============================================================
 * Transformer 2：Epstein 替换规则（仅 TextDocument）
 * ============================================================ */

class EpsteinNameTransformer {
public:
    std::string operator()(Document* doc) const {
        TextDocument* td = dynamic_cast<TextDocument*>(doc);
        if (!td) return "NOT A TEXT FILE";

        std::string txt = td->content();

        if (txt == "Trump") {
            return "MR.BUNNY";
        }
        if (txt == "Clinton") {
            return "MR.RABBIT";
        }
        return txt;
    }
};

/* ============================================================
 * Transformer 3：单词反转（仅 TextDocument）
 * ============================================================ */

class ReverseWordTransformer {
public:
    std::string operator()(Document* doc) const {
        TextDocument* td = dynamic_cast<TextDocument*>(doc);
        if (!td) return "NOT A TEXT FILE";
        return reverseWords(td->content());
    }
};

/* ============================================================
 * Transformer 4：InversePdfPagesTransformer（就地修改）
 * PDF / EncryptedPDF 都适用
 * 直接反转 pdf->pages
 * ============================================================ */

class InversePdfPagesTransformer {
public:
    std::string operator()(Document* doc) const {
        auto* pdf = dynamic_cast<PDFDocument*>(doc);
        if (!pdf) return "NOT A PDF FILE";

        auto& pages = pdf->getPages();
        std::reverse(pages.begin(), pages.end());

        return pdf->content();
    }
};

#endif
