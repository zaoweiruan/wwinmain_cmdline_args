#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fcntl.h>
// 全局配置变量（存储命令行参数解析结果）
struct Config {
    std::wstring output_path = L"clipboard.log"; // 默认输出文件
    bool verbose = false;                        // 是否显示详细日志
    bool show_help = false;                       // 是否显示帮助信息
};

// 解析宽字符命令行参数
Config parse_command_line(LPWSTR lpCmdLine) {
    Config cfg;
    std::vector<std::wstring> args;

    // 分割 lpCmdLine 为单个参数（简易分割，处理空格分隔的参数）
    wchar_t* token = wcstok(lpCmdLine, L" ");
    while (token != nullptr) {
        args.emplace_back(token);
        token = wcstok(nullptr, L" ");
    }

    // 解析参数
    for (size_t i = 0; i < args.size(); ++i) {
        if (args[i] == L"--output" || args[i] == L"-o") {
            if (i + 1 < args.size()) {
                cfg.output_path = args[++i]; // 取后续参数作为输出路径
            } else {
                cfg.show_help = true;
                std::wcerr << L"错误：--output 需要指定文件路径" << std::endl;
            }
        } else if (args[i] == L"--verbose" || args[i] == L"-v") {
            cfg.verbose = true;
        } else if (args[i] == L"--help" || args[i] == L"-h") {
            cfg.show_help = true;
        } else {
            cfg.show_help = true;
            std::wcerr << L"错误：未知参数 " << args[i] << std::endl;
        }
    }

    return cfg;
}

// 显示帮助信息
void show_help(HINSTANCE hInstance) {
    std::wcout << L"剪贴板监听工具" << std::endl;
    std::wcout << L"用法：ClipboardListener [选项]" << std::endl;
    std::wcout << L"选项：" << std::endl;
    std::wcout << L"  --output <路径> (-o)  剪贴板内容保存路径（默认：clipboard.log）" << std::endl;
    std::wcout << L"  --verbose (-v)        显示详细日志" << std::endl;
    std::wcout << L"  --help (-h)           显示此帮助信息" << std::endl;
}

// ==== UTF-8 控制台设置 ====
void setup_utf8_console() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U8TEXT);
}

// 剪贴板监听相关函数（简化版，仅示意）
void StartClipboardListener() {
    // 实际项目中替换为真实的剪贴板监听逻辑
    std::wcout << L"已启动剪贴板监听（按 Ctrl+C 退出）..." << std::endl;
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// 程序入口（宽字符版本）
int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow
) {
    // 1. 解析命令行参数
    Config cfg = parse_command_line(lpCmdLine);

    // 2. 初始化控制台（支持 UTF-8 输出）
    setup_utf8_console();

    // 3. 处理帮助信息
    if (cfg.show_help) {
        show_help(hInstance);
        return 0;
    }

    // 4. 输出参数配置（演示用）
    std::wcout << L"===== 配置信息 =====" << std::endl;
    std::wcout << L"输出文件路径：" << cfg.output_path << std::endl;
    std::wcout << L"详细日志：" << (cfg.verbose ? L"开启" : L"关闭") << std::endl;

    // 5. 启动剪贴板监听
   // StartClipboardListener();

    return 0;
}