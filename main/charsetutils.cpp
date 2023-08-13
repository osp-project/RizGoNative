#include <codecvt>
#include <string>
#include <locale>

// 定义一个函数，用 codecvt，输入 std::string，输出已经转 UTF-8 的 std::string
std::string convert_to_utf8(const std::string& input)
{
    // 定义一个转换器
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    // 将 input 转换为宽字符字符串
    std::wstring wstr = conv.from_bytes(input);
    // 将 wstr 转换为 UTF-8 编码的字符串
    std::string output = conv.to_bytes(wstr);
    // 返回 output
    return output;
}