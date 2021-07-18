print("貸款總額")
loan_amount = int(input())
print("還款期限(yr)")
loan_term_year = int(input())
print("寬期限(yr)")
grace_period_year = int(input())
print()
r_year = 0.0133

num_month = 12
loan_term_month = loan_term_year * num_month
grace_period_month = grace_period_year * num_month
r_month = r_year / num_month

only_interest = round(r_month * loan_amount)
Constant_Payment_loan = [only_interest] * grace_period_month
Constant_Amortization_loan = [only_interest] * grace_period_month
principle_and_interest = round(loan_amount * ((1 + r_month) ** (loan_term_month - grace_period_month)) * r_month / (((1 + r_month) ** (loan_term_month - grace_period_month)) - 1))
Constant_Payment_loan += [principle_and_interest] * (loan_term_month - grace_period_month)
# print(Constant_Payment_loan)
print("本息平均攤還")
print(f"\t第1個月 ~ 第{grace_period_month}個月(寬限期):\t{only_interest}")
print(f"\t第{grace_period_month + 1}個月 ~ 第{loan_term_month}個月:\t \t{principle_and_interest}")
for i in range(loan_term_month - grace_period_month):
	principle_part = loan_amount / (loan_term_month - grace_period_month)
	Constant_Amortization_loan.append(round(principle_part + (loan_amount - principle_part * i) * r_month))
print("\n本金平均攤還")
for i in range(len(Constant_Amortization_loan)):
	print(f"\t第{i + 1}個月: \t{Constant_Amortization_loan[i]}")