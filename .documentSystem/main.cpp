#include <iostream>
#include <vector>
#include "Document.h"
#include "Transformers.h"
#include "TransformerIterator.h"
#include "StatCollectorIterator.h"
#include "StatCollectors.h"
#include "Predicates.h"

int main() {
    using namespace std;

    // ===============================
    // 创建文档集合
    // ===============================
    vector<Document*> docs = {
        new TextDocument("Doc1", "Hello world"),
        new PDFDocument("Doc2", {"Page1", "Page2"}),
        new EncryptedPDFDocument("Doc3", {"Secret1", "Secret2", "Secret3", "Secret4"}),
        new TextDocument("Doc4", "Trump"),
        new TextDocument("Doc5", "Clinton"),
        new PDFDocument("Doc6", {"Intro", "Chapter1", "Chapter2"}),
        new EncryptedPDFDocument("Doc7", {"Hidden1", "Hidden2"}),
        new TextDocument("Doc8", "Make La Terre Great Again!")
    };

    cout << "========== TransformerIterator 示例 ==========" << endl;

    // 0. IdentityTransformer
    TransformerIterator<vector<Document*>, IdentityTransformer> identityIt(docs, IdentityTransformer());
    cout << "IdentityTransformer results:" << endl;
    while (identityIt.goodbon()) {
        cout << *identityIt << endl;
        ++identityIt;
    }

    cout << "\n";

    // 1. UppercaseTransformer
    TransformerIterator<vector<Document*>, UppercaseTransformer> upperIt(docs, UppercaseTransformer());
    cout << "UppercaseTransformer results:" << endl;
    while (upperIt.goodbon()) {
        cout << *upperIt << endl;
        ++upperIt;
    }

    cout << "\n";

    // 2. EpsteinNameTransformer
    TransformerIterator<vector<Document*>, EpsteinNameTransformer> epsteinIt(docs, EpsteinNameTransformer());
    cout << "EpsteinNameTransformer results:" << endl;
    while (epsteinIt.goodbon()) {
        cout << *epsteinIt << endl;
        ++epsteinIt;
    }

    cout << "\n";

    // 3. ReverseWordTransformer
    TransformerIterator<vector<Document*>, ReverseWordTransformer> revIt(docs, ReverseWordTransformer());
    cout << "ReverseWordTransformer results:" << endl;
    while (revIt.goodbon()) {
        cout << *revIt << endl;
        ++revIt;
    }

    cout << "\n";

    // 4. InversePdfPagesTransformer
    TransformerIterator<vector<Document*>, InversePdfPagesTransformer> inversePdfPagesIt(docs, InversePdfPagesTransformer());
    cout << "InversePdfPagesTransformer results:" << endl;
    while (inversePdfPagesIt.goodbon()) {
        cout << *inversePdfPagesIt << endl;
        ++inversePdfPagesIt;
    }

    cout << "\n========== StatCollectorIterator + PredicateCounter 示例 ==========" << endl;

    // 创建统计迭代器
    StatCollectorIterator<vector<Document*>> statIt(docs);

    // 统计 TextDocument
    PredicateCounter<Document, IsA<TextDocument>> textCounter(IsA<TextDocument>{});
    statIt.run(textCounter);
    cout << "TextDocument count: " << textCounter.getCount() << endl;

    // 统计 PDFDocument (包括加密版)
    PredicateCounter<Document, IsA<PDFDocument>> pdfCounter(IsA<PDFDocument>{});
    statIt.run(pdfCounter);
    cout << "PDFDocument count: " << pdfCounter.getCount() << endl;

    // 统计 EncryptedPDFDocument
    PredicateCounter<Document, IsA<EncryptedPDFDocument>> encCounter(IsA<EncryptedPDFDocument>{});
    statIt.run(encCounter);
    cout << "EncryptedPDFDocument count: " << encCounter.getCount() << endl;

    cout << "\n========== 综合统计示例 ==========" << endl;

    // 统计所有 PDF 页面总数（包括加密版）
    size_t totalPages = 0;
    for (auto d : docs) {
        PDFDocument* pdf = dynamic_cast<PDFDocument*>(d);
        if (pdf) {
            totalPages += pdf->pageCount();
        }
    }
    cout << "Total pages across all PDF documents (including encrypted): " << totalPages << endl;

    // 统计所有 加密版PDF 页面总数
    size_t totalPagesEncrypted = 0;
    for (auto d : docs) {
        EncryptedPDFDocument* pdf = dynamic_cast<EncryptedPDFDocument*>(d);
        if (pdf) {
            totalPagesEncrypted += pdf->pageCount();
        }
    }
    cout << "Total pages across all encrypted PDF documents: " << totalPagesEncrypted << endl;

    // 统计所有 TextDocument 的文本长度总和
    size_t totalTextLength = 0;
    for (auto d : docs) {
        TextDocument* td = dynamic_cast<TextDocument*>(d);
        if (td) {
            totalTextLength += td->content().size();
        }
    }
    cout << "Total characters across all TextDocuments: " << totalTextLength << endl;

    // 清理动态分配
    for (auto d : docs) delete d;

    return 0;
}
