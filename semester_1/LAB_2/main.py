def isBalanced(expression):
    stack = []
    for char in expression:
        if char == '(':
            stack.append(char)
        elif char == ')':
            if not stack:
                return False
            stack.pop()
    return len(stack) == 0

def Precedence(op):
    if op in ('+', '-'):
        return 1
    elif op in ('*', '/'):
        return 2
    return 0

def ApplyOperator(operators, values):
    operator = operators.pop()
    right = values.pop()
    left = values.pop()
    
    if operator == '+':
        values.append(left + right)
    elif operator == '-':
        values.append(left - right)
    elif operator == '*':
        values.append(left * right)
    elif operator == '/':
        if right == 0:
            raise ValueError("Деление на ноль")
        values.append(left / right)

def EvaluateExpression(expression):
    if expression[-1] != "=":
        raise ValueError("В конце должен быть =")
    expression = expression[:-1]
    if not isBalanced(expression):
        raise ValueError("Неверная расстановка скобок")
    
    values = []
    operators = []
    i = 0
    n = len(expression)
    
    while i < n:
        if expression[i].isdigit():
            j = i
            while j < n and (expression[j].isdigit() or expression[j] == '.'):
                j += 1
            num_str = expression[i:j]
            if '.' in num_str:
                num = float(num_str)
            else:
                num = int(num_str)
            values.append(num)
            i = j
        else:
            if expression[i] == '(':
                operators.append(expression[i])
                i += 1
            elif expression[i] == ')':
                while operators and operators[-1] != '(':
                    ApplyOperator(operators, values)
                if not operators:
                    raise ValueError("Неверная расстановка скобок")
                operators.pop()
                i += 1
            elif expression[i] in '+-*/':
                if (expression[i] == '-' and 
                    (i == 0 or expression[i-1] in '(+-*/')):
                    values.append(0)
                while (operators and operators[-1] != '(' and Precedence(operators[-1]) >= Precedence(expression[i])):
                    ApplyOperator(operators, values)
                operators.append(expression[i])
                i += 1
            else:
                raise ValueError(f"Недопустимый символ: '{expression[i]}'")
    while operators:
        if operators[-1] == '(':
            raise ValueError("Неверная расстановка скобок")
        ApplyOperator(operators, values) 
    return values[0]

def main():
    try:
        expression = input("Введите математическое выражение: ")
        result = EvaluateExpression(expression)
        print(f"Результат: {result}")        
    except ValueError as e:
        print(f"Ошибка: {e}")
    except Exception as e:
        print(f"Неожиданная ошибка: {e}")

if __name__ == "__main__":
    main()