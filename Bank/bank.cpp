#include <string>

// Module đánh giá và phê duyệt hồ sơ vay tự động
std::string verification(int age, float income, int credit_score, char employment) {
    // Bước 1: Validate dữ liệu đầu vào theo điều kiện ràng buộc
    if (age < 18 || age > 65) return "Invalid Input";
    if (income < 5.0f || income > 500.0f) return "Invalid Input";
    if (credit_score < 300 || credit_score > 850) return "Invalid Input";
    if (employment != 'C' && employment != 'F') return "Invalid Input";

    // Bước 2: Đánh giá nhóm nợ xấu / rủi ro tín dụng
    int risk = 0; // Thang đo: 1 = Rủi ro cao, 2 = Rủi ro vừa, 3 = Rủi ro thấp
    if (credit_score >= 300 && credit_score <= 500) risk = 1;
    else if (credit_score >= 501 && credit_score <= 700) risk = 2;
    else if (credit_score >= 701 && credit_score <= 850) risk = 3;

    // Bước 3: Áp dụng bảng quy tắc để định tuyến hồ sơ
    if (risk == 1) {
        return "REJECT"; // Từ chối ngay nếu rủi ro chạm ngưỡng High
    }

    if (income < 15.0f) {
        // Nhóm thu nhập dưới chuẩn
        if (employment == 'F' || risk == 2) return "REJECT";
        if (employment == 'C' && risk == 3) return "MANUAL REVIEW";
    } else {
        // Nhóm thu nhập đạt chuẩn (từ 15 triệu trở lên)
        if (employment == 'C') return "APPROVED";
        if (employment == 'F') return "MANUAL REVIEW";
    }

    return "UNKNOWN";
}