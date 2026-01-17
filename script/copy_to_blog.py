#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
脚本功能：将Ex文件夹的内容按格式拷贝到blog.md中
- 对于Ex单文件（如Ex01.cpp），以 # Ex01 为标题
- 对于Ex文件夹（如Ex22&23/），以 # Ex22&23 文件夹 为标题，其子文件用 ## 文件名
"""

import os
import re
from pathlib import Path


def get_language_from_extension(filename):
    """根据文件扩展名返回代码块的语言标记"""
    ext_map = {
        '.cpp': 'cpp',
        '.h': 'h',
        '.hpp': 'h',
        '.c': 'c',
        '.py': 'python',
        '.js': 'javascript',
        '.java': 'java',
        '.md': 'markdown',
        '.txt': 'text',
    }
    ext = Path(filename).suffix.lower()
    return ext_map.get(ext, 'text')


def read_file_content(filepath):
    """读取文件内容，尝试不同编码"""
    encodings = ['utf-8', 'gbk', 'latin-1']
    for encoding in encodings:
        try:
            with open(filepath, 'r', encoding=encoding) as f:
                return f.read()
        except (UnicodeDecodeError, FileNotFoundError):
            continue
    return None


def extract_ex_number(name):
    """从文件名中提取Ex编号，用于排序"""
    match = re.match(r'Ex(\d+)', name)
    if match:
        return int(match.group(1))
    return float('inf')


def process_ex_file(filepath, ex_name):
    """处理单个Ex文件"""
    content = read_file_content(filepath)
    if content is None:
        return f"# {ex_name}\n```\n无法读取文件内容\n```\n\n"
    
    lang = get_language_from_extension(filepath)
    return f"# {ex_name}\n```{lang}\n{content}\n```\n\n"


def process_ex_folder(folder_path, ex_name):
    """处理Ex文件夹，生成带子文件的内容"""
    result = f"# {ex_name} 文件夹\n"
    
    # 获取文件夹中的所有文件（排除可执行文件和其他无关文件）
    files = []
    for item in os.listdir(folder_path):
        item_path = os.path.join(folder_path, item)
        if os.path.isfile(item_path):
            # 排除没有扩展名的文件（通常是编译后的可执行文件）
            if '.' in item or item.endswith(('.cpp', '.h', '.hpp', '.c')):
                files.append(item)
    
    # 排序文件：优先显示头文件，然后是源文件
    def file_sort_key(filename):
        ext = Path(filename).suffix.lower()
        if ext in ['.h', '.hpp']:
            return (0, filename)
        elif ext in ['.cpp', '.c']:
            return (1, filename)
        else:
            return (2, filename)
    
    files.sort(key=file_sort_key)
    
    # 为每个文件生成内容
    for filename in files:
        filepath = os.path.join(folder_path, filename)
        content = read_file_content(filepath)
        
        if content is None:
            result += f"## {filename}\n```\n无法读取文件内容\n```\n\n"
        else:
            lang = get_language_from_extension(filename)
            result += f"## {filename}\n```{lang}\n{content}\n```\n\n"
    
    return result


def main():
    """主函数：扫描工作区中的Ex文件和文件夹，生成blog内容"""
    workspace_path = Path(__file__).parent
    output_lines = []
    
    # 添加文件头部说明
    output_lines.append(">下载练习册题面以及想要拉到本地跑代码可以去 [CPlus 仓库](https://github.com/ceilf6/CPlusPlus)")
    output_lines.append("或者终端输入命令")
    output_lines.append("```")
    output_lines.append("git clone https://github.com/ceilf6/CPlusPlus")
    output_lines.append("```")
    output_lines.append("> 如果翻不了墙也可以用国内平替 [CPlus 仓库（国内）](https://gitee.com/ceilf6/SHU_CPlus)")
    output_lines.append("# README")
    output_lines.append("> ⚠️ 由于时间紧迫，这是我在回校后一周内同时复习多门课程、抽空完成的，如有不合理之处，欢迎随时交流，或直接在仓库提 Issue / PR。")
    output_lines.append("```")
    output_lines.append("## 🧠 关于算法的一些浅见（快速入门向）")
    output_lines.append("")
    output_lines.append("算法是基于计算机思想对数据进行管理和高效操作的艺术。它往往源于我们对问题结构的观察和抽象：")
    output_lines.append("")
    output_lines.append("- **分治思想** → 催生了归并排序、快速排序等；")
    output_lines.append("- **树形结构** → 发展出了深度优先搜索（DFS）、字典树、线段树等；")
    output_lines.append("- **懒更新** → 解决了高频动态区间修改的问题（如线段树懒标记）；")
    output_lines.append("- **重叠子问题** → 促成了动态规划，借助状态转移 + 递归回溯降低复杂度。")
    output_lines.append("")
    output_lines.append("💬 顺带一提：  ")
    output_lines.append("算法思想也广泛应用于其他领域。例如在前端开发中，理解\"树形结构\"的逻辑，可以：")
    output_lines.append("")
    output_lines.append("- 清晰描述 UI 组件的层级关系；")
    output_lines.append("- 在\"分叉节点\"复用公共组件；")
    output_lines.append("- 通过 `props` 注入差异化逻辑，实现**高度复用**和**低耦合工程**。")
    output_lines.append("")
    output_lines.append("---")
    output_lines.append("")
    output_lines.append("## 🤝 一起进步！")
    output_lines.append("")
    output_lines.append("欢迎各位大佬一起探讨与交流，互相学习，持续成长 🚀  ")
    output_lines.append("👉 有问题随时提 Issue，或者发起 PR～")
    output_lines.append("")
    output_lines.append("---")
    output_lines.append("")
    output_lines.append("> 在做完算法册题目后我发现本门课更加注重对 C++ 基础特性的把握以及工程化中的安全实践，对同学们后面工作有很大帮助")
    output_lines.append("```")
    
    # 收集所有Ex项目（文件和文件夹）
    ex_items = []
    
    for item in os.listdir(workspace_path):
        item_path = os.path.join(workspace_path, item)
        
        # 检查是否为Ex开头的文件
        if item.startswith('Ex') and item.endswith('.cpp'):
            ex_name = item[:-4]  # 移除.cpp扩展名
            ex_items.append(('file', ex_name, item_path))
        
        # 检查是否为Ex开头的文件夹
        elif item.startswith('Ex') and os.path.isdir(item_path):
            ex_items.append(('folder', item, item_path))
    
    # 按Ex编号排序
    ex_items.sort(key=lambda x: extract_ex_number(x[1]))
    
    # 处理每个Ex项目
    for item_type, ex_name, item_path in ex_items:
        if item_type == 'file':
            output_lines.append(process_ex_file(item_path, ex_name))
        elif item_type == 'folder':
            output_lines.append(process_ex_folder(item_path, ex_name))
    
    # 写入到blog.md
    output_file = workspace_path / 'blog.md'
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write('\n'.join(output_lines))
    
    print(f"✅ 成功生成 blog.md！")
    print(f"📝 处理了 {len(ex_items)} 个Ex项目")
    print(f"📍 输出文件：{output_file}")


if __name__ == '__main__':
    main()
