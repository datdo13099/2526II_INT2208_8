#include <iostream>
#include <string>
#include <iomanip>

// Prototype của hàm nghiệp vụ cần test
std::string verification(int age, float income, int credit_score, char employment);

// Framework test tự chế mô phỏng theo chuẩn OOP
class TestLoanApproval {
private:
    int total_tests = 0;
    int passed_tests = 0;

    // Hàm so sánh kết quả thực tế với mong đợi (Assertion)
    void assertEqual(const std::string& actual, const std::string& expected, const std::string& test_id) {
        total_tests++;
        if (actual == expected) {
            passed_tests++;
            std::cout << "[PASS] " << test_id << "\n";
        } else {
            std::cout << "[FAIL] " << test_id << " | Expected: " << expected << " | Actual: " << actual << "\n";
        }
    }

public:
    // Giai đoạn 1: Bắt lỗi input đầu vào (Negative Testing)
    void test_invalid_input() {
        std::cout << "\n--- Chay kiem tra cac ca Input loi ---\n";
        // Test cận dưới và cận trên của độ tuổi
        assertEqual(verification(17, 50.0f, 700, 'C'), "Invalid Input", "TC_01");
        assertEqual(verification(66, 50.0f, 700, 'C'), "Invalid Input", "TC_02");
        
        // Test mốc thu nhập tối thiểu và tối đa
        assertEqual(verification(30, 4.9f, 700, 'C'), "Invalid Input", "TC_03");
        assertEqual(verification(30, 500.1f, 700, 'C'), "Invalid Input", "TC_04");
        
        // Test điểm tín dụng ngoài luồng
        assertEqual(verification(30, 50.0f, 299, 'C'), "Invalid Input", "TC_05");
        assertEqual(verification(30, 50.0f, 851, 'C'), "Invalid Input", "TC_06");
        
        // Test mã công việc không tồn tại trong hệ thống
        assertEqual(verification(30, 50.0f, 700, 'X'), "Invalid Input", "TC_07");
    }

    // Giai đoạn 2: Kiểm thử luồng xử lý chính (Positive/Business Testing)
    
    // Các kịch bản từ chối thẳng hồ sơ
    void test_reject_cases() {
        std::cout << "\n--- Kiem tra phan luong REJECT ---\n";
        // Nhóm rủi ro cao: Auto tạch
        assertEqual(verification(30, 5.0f, 300, 'C'), "REJECT", "TC_08");
        assertEqual(verification(65, 5.0f, 500, 'F'), "REJECT", "TC_09");
        assertEqual(verification(30, 500.0f, 400, 'C'), "REJECT", "TC_10");
        
        // Lương thấp kèm rủi ro mức khá: Bỏ qua
        assertEqual(verification(19, 5.0f, 501, 'C'), "REJECT", "TC_11");
        assertEqual(verification(30, 14.9f, 600, 'C'), "REJECT", "TC_12");
        
        // Lương thấp lại làm tự do: Không hỗ trợ
        assertEqual(verification(64, 5.0f, 701, 'F'), "REJECT", "TC_13");
        assertEqual(verification(30, 14.9f, 850, 'F'), "REJECT", "TC_14");
    }

    // Các kịch bản duyệt tự động
    void test_APPROVED_cases() {
        std::cout << "\n--- Kiem tra phan luong APPROVED ---\n";
        // Đạt chuẩn thu nhập, rủi ro chấp nhận được và có hợp đồng rõ ràng
        assertEqual(verification(30, 15.0f, 501, 'C'), "APPROVED", "TC_17");
        assertEqual(verification(30, 500.0f, 700, 'C'), "APPROVED", "TC_18");
        assertEqual(verification(18, 15.0f, 701, 'C'), "APPROVED", "TC_19");
        assertEqual(verification(65, 500.0f, 850, 'C'), "APPROVED", "TC_20");
    }

    // Các kịch bản cần chuyển thẩm định viên duyệt tay
    void test_manual_review_cases() {
        std::cout << "\n--- Kiem tra phan luong MANUAL REVIEW ---\n";
        // Lương chưa đạt mốc 15tr nhưng điểm tín dụng đẹp, có hợp đồng
        assertEqual(verification(18, 5.0f, 701, 'C'), "MANUAL REVIEW", "TC_15");
        assertEqual(verification(65, 14.9f, 850, 'C'), "MANUAL REVIEW", "TC_16");
        
        // Lương cao nhưng làm tự do, rủi ro ở mức trung bình - thấp
        assertEqual(verification(30, 15.0f, 501, 'F'), "MANUAL REVIEW", "TC_21");
        assertEqual(verification(30, 500.0f, 700, 'F'), "MANUAL REVIEW", "TC_22");
        assertEqual(verification(30, 15.0f, 701, 'F'), "MANUAL REVIEW", "TC_23");
        assertEqual(verification(30, 500.0f, 850, 'F'), "MANUAL REVIEW", "TC_24");
    }

    // Chạy test tại các điểm giao thoa điều kiện (Boundary Interfaces)
    void test_at_interface() {
        std::cout << "\n--- Kiem tra cac ca Boundary Interfaces ---\n";
        assertEqual(verification(44, 100.0f, 500, 'C'), "REJECT", "TC_25");
        assertEqual(verification(44, 100.0f, 501, 'C'), "APPROVED", "TC_26");
        assertEqual(verification(44, 14.9f, 750, 'C'), "MANUAL REVIEW", "TC_27");
        assertEqual(verification(44, 15.0f, 750, 'C'), "APPROVED", "TC_28");
    }

    // Bộ điều khiển kích hoạt tất cả các suites
    void run() {
        test_invalid_input();
        test_reject_cases();
        test_APPROVED_cases();
        test_manual_review_cases();
        test_at_interface();

        std::cout << "\n======================================\n";
        std::cout << "Tong hop ket qua: " << passed_tests << " / " << total_tests << " kịch bản PASSED.\n";
        std::cout << "======================================\n";
    }
};

// Entry point của chương trình test
int main() {
    TestLoanApproval test_suite;
    test_suite.run();
    return 0;
}