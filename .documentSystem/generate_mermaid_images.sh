#!/bin/bash

# 在 cpp-from-teacher 目录下运行此脚本
# 它会提取所有 Mermaid 图表并生成 PNG 图片

cd "$(dirname "$0")"

# 创建图片目录
mkdir -p images

echo "正在提取 Mermaid 图表..."

# 提取图1 - Document 继承层次
cat > images/diagram1.mmd << 'EOF'
classDiagram
    class Document {
        <<abstract>>
        #string title
        +Document(const string& t)
        +~Document() virtual
        +content() string*
        +getTitle() const string&
    }

    class TextDocument {
        -string text
        +TextDocument(string t, string txt)
        +content() string
    }

    class PDFDocument {
        #vector~string~ pages
        +PDFDocument(string t, vector p)
        +content() string
        +pageCount() size_t
        +getPages() vector&
    }

    class EncryptedPDFDocument {
        +EncryptedPDFDocument(string t, vector p)
        +content() string
        +getPages() from PDFDocument
    }

    Document <|-- TextDocument
    Document <|-- PDFDocument
    PDFDocument <|-- EncryptedPDFDocument
EOF

# 提取图2 - StatCollector
cat > images/diagram2.mmd << 'EOF'
classDiagram
    class StatCollector~T~ {
        <<abstract>>
        +~StatCollector() virtual
        +process(T* ptr)* void
    }

    class PredicateCounter~T_Predicate~ {
        -Predicate pred
        -int count
        +PredicateCounter(Predicate p)
        +process(T* ptr) void
        +getCount() int
    }

    StatCollector~T~ <|-- PredicateCounter~T_Predicate~
EOF

# 提取图3 - Iterator
cat > images/diagram3.mmd << 'EOF'
classDiagram
    class TransformerIterator~CONTAINER_Transformer~ {
        -const CONTAINER& container
        -const_iterator current
        -Transformer transformer
        +TransformerIterator(CONTAINER c, Transformer t)
        +operator++() void
        +goodbon() bool
        +operator*() string
    }

    class StatCollectorIterator~CONTAINER~ {
        -CONTAINER& container
        -iterator it
        +StatCollectorIterator(CONTAINER c)
        +run(Collector& col) void
        +goodbon() bool
    }
EOF

# 提取图4 - Transformers
cat > images/diagram4.mmd << 'EOF'
classDiagram
    class IdentityTransformer {
        <<functor>>
        +operator()(Document* doc) string
    }

    class UppercaseTransformer {
        <<functor>>
        +operator()(Document* doc) string
    }

    class EpsteinNameTransformer {
        <<functor>>
        +operator()(Document* doc) string
    }

    class ReverseWordTransformer {
        <<functor>>
        +operator()(Document* doc) string
    }

    class InversePdfPagesTransformer {
        <<functor>>
        +operator()(Document* doc) string
    }
EOF

# 提取图5 - Predicates
cat > images/diagram5.mmd << 'EOF'
classDiagram
    class IsA~Target~ {
        <<functor>>
        +operator()(T* ptr) bool
    }

    class WordCountPredicate {
        <<functor>>
        -int totalWords
        +WordCountPredicate()
        +operator()(Document* doc) void
        +getCount() int
    }

    class PageCountPredicate {
        <<functor>>
        -int totalPages
        +PageCountPredicate()
        +operator()(Document* doc) void
        +getCount() int
    }
EOF

# 提取图6 - 整体关系
cat > images/diagram6.mmd << 'EOF'
graph TB
    subgraph Documents["文档类"]
        D[Document 抽象类]
        TD[TextDocument]
        PD[PDFDocument]
        EPD[EncryptedPDFDocument]
    end

    subgraph Transformers["转换器函数对象"]
        T1[IdentityTransformer]
        T2[UppercaseTransformer]
        T3[EpsteinNameTransformer]
        T4[ReverseWordTransformer]
        T5[InversePdfPagesTransformer]
    end

    subgraph Predicates["谓词函数对象"]
        P1["IsA&lt;Target&gt;"]
        P2[WordCountPredicate]
        P3[PageCountPredicate]
    end

    subgraph Iterators["迭代器"]
        TI[TransformerIterator]
        SI[StatCollectorIterator]
    end

    subgraph Collectors["统计器"]
        SC[StatCollector 抽象类]
        PC[PredicateCounter]
    end

    D --> TD
    D --> PD
    PD --> EPD

    TI -->|使用| Transformers
    TI -->|遍历| Documents

    SI -->|使用| Collectors
    SI -->|遍历| Documents

    PC -->|使用| Predicates
    SC --> PC
EOF

echo "正在生成 PNG 图片..."

# 使用 mermaid-cli 生成图片
for i in {1..6}; do
    echo "生成图 $i..."
    npx -p @mermaid-js/mermaid-cli mmdc -i images/diagram$i.mmd -o images/diagram$i.png -b transparent -w 1200
done

echo "完成！图片已保存到 images/ 目录"
ls -lh images/*.png
