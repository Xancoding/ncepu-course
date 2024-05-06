#include <iostream>

class Loan {
public:
    virtual ~Loan() {}
    virtual void Show() const = 0;  // 纯虚函数，计算并显示还款信息

protected:
    double m_loan_amount;  // 贷款金额
    int m_loan_years;     // 还款年限
    double m_interest_rate;  // 年利率

public:
    Loan(double amount, int years, double rate)
            : m_loan_amount(amount), m_loan_years(years), m_interest_rate(rate) {}
};

#include <cmath>

// 等额本息还款方式
class EqualPrincipalAndInterest : public Loan {
public:
    EqualPrincipalAndInterest(double amount, int years, double rate)
            : Loan(amount, years, rate) {}

    void Show() const override {
        double monthly_payment = CalculateMonthlyPayment();
        std::cout << "等额本息还款方式：" << std::endl;
        std::cout << "每月还款额：" << monthly_payment << std::endl;
        std::cout << "总还款额：" << monthly_payment * m_loan_years * 12 << std::endl;
        std::cout << "总利息：" << monthly_payment * m_loan_years * 12 - m_loan_amount << std::endl;

        for (int i = 1; i <= m_loan_years * 12; ++i) {
            double monthly_principal = monthly_payment - m_loan_amount * m_interest_rate / 12;
            double monthly_interest = monthly_payment - monthly_principal;
            std::cout << "第 " << i << " 个月还款：" << std::endl;
            std::cout << "    本金：" << monthly_principal << std::endl;
            std::cout << "    利息：" << monthly_interest << std::endl;
        }
    }

private:
    double CalculateMonthlyPayment() const {
        double monthly_interest_rate = m_interest_rate / 12 / 100;
        return m_loan_amount * monthly_interest_rate * pow(1 + monthly_interest_rate, m_loan_years * 12) /
               (pow(1 + monthly_interest_rate, m_loan_years * 12) - 1);
    }
};

// 等额本金还款方式
class EqualPrincipal : public Loan {
public:
    EqualPrincipal(double amount, int years, double rate) : Loan(amount, years, rate) {}

    void Show() const override {
        double monthly_principal = m_loan_amount / (m_loan_years * 12);
        double total_interest = 0;
        std::cout << "等额本金还款方式：" << std::endl;
        std::cout << "每月还款额：" << monthly_principal + m_loan_amount * m_interest_rate / 12 / 100 << std::endl;
        std::cout << "总还款额：" << (monthly_principal + m_loan_amount * m_interest_rate / 12 / 100) * m_loan_years * 12 << std::endl;

        for (int i = 1; i <= m_loan_years * 12; ++i) {
            double monthly_interest = m_loan_amount * m_interest_rate / 12 / 100 * (m_loan_years * 12 - i + 1) / (m_loan_years * 12);
            total_interest += monthly_interest;
            std::cout << "第 " << i << " 个月还款：" << std::endl;
            std::cout << "    本金：" << monthly_principal << std::endl;
            std::cout << "    利息：" << monthly_interest << std::endl;
        }

        std::cout << "总利息：" << total_interest << std::endl;
    }
};

void ShowLoanInfo(const Loan& loan) {
    loan.Show();
}

int main() {
    const double amount = 1000000;  // 贷款金额
    const int years = 30;         // 还款年限
    const double rate = 4.9;       // 年利率

    // 创建等额本息和等额本金对象
    EqualPrincipalAndInterest epi(amount, years, rate);
    EqualPrincipal ep(amount, years, rate);

    // 显示还款信息
    ShowLoanInfo(epi);
    std::cout << std::endl;
    ShowLoanInfo(ep);

    return 0;
}
