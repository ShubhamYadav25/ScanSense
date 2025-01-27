# 🐛 C++ Code Analyzer

A lightweight tool to detect **syntax errors** and **logical bugs** in C++ code. This tool uses string parsing and pattern matching to identify potential issues in your codebase.

---

## 🛠️ Features

### **Syntax Analysis** 🔍
These methods detect common syntax errors in C++ code:

1. **`checkMissingSemicolons`**  
   🚨 Detects missing semicolons at the end of statements.

2. **`checkUndefinedVariables`**  
   🚨 Identifies variables that are used but not defined.

3. **`checkMismatchedBrackets`**  
   🚨 Checks for mismatched `{}`, `()`, or `[]` brackets.

4. **`checkTypeMismatches`**  
   🚨 Detects potential type mismatches in assignments or function calls.

---

### **Logical Error Detection** 🧠
These methods identify common logical bugs in C++ code:

1. **`checkIncorrectLoopConditions`**  
   🔄 Detects incorrect loop conditions, including **off-by-one errors**.

2. **`checkIncorrectBooleanLogic`**  
   🔍 Identifies incorrect usage of boolean logic (e.g., `&&` vs `||`).

3. **`checkIncorrectComparisonOperators`**  
   ⚖️ Detects incorrect comparison operators (e.g., `==` vs `=`).

4. **`checkIncorrectOrderOfOperations`**  
   🧮 Flags potential issues with operator precedence and order of operations.

5. **`checkIncorrectLoopVariableUpdates`**  
   🔄 Identifies loops with incorrect or missing variable updates (e.g., infinite loops).

6. **`checkIncorrectSwitchCaseLogic`**  
   🔀 Detects `switch` statements missing a `default` case or incorrect fall-through logic.

7. **`checkIncorrectFunctionReturnLogic`**  
   🔙 Identifies functions that may not return a value on all code paths.

8. **`checkIncorrectRecursionLogic`**  
   🔄 Detects recursive functions that may lack a base case.

9. **`checkIncorrectEdgeCaseHandling`**  
   🎯 Flags potential missing handling of edge cases (e.g., null values, empty inputs).

10. **`checkIncorrectStateTransitions`**  
    🔄 Detects incorrect state transitions in state machines or stateful logic.

11. **`checkIncorrectMathematicalFormulas`**  
    🧮 Identifies potential mathematical errors, such as division by zero.

12. **`checkIncorrectStringOrArrayManipulation`**  
    📜 Detects incorrect handling of strings or arrays (e.g., out-of-bounds access).

13. **`checkIncorrectNullOrEmptyHandling`**  
    🚫 Flags potential issues with null or empty value handling.

14. **`checkIncorrectFlagOrEnumUsage`**  
    🚩 Detects incorrect usage of flags or enums.

15. **`checkIncorrectErrorHandlingLogic`**  
    ❌ Identifies incorrect error handling (e.g., missing error checks).

16. **`checkIncorrectAlgorithmImplementation`**  
    🧠 Detects logical errors in algorithm implementations.

17. **`checkIncorrectShortCircuiting`**  
    ⚡ Flags incorrect use of logical short-circuiting (e.g., `&&` or `||`).

18. **`checkIncorrectTimeOrDateLogic`**  
    🕒 Detects incorrect handling of time or date logic.

19. **`checkIncorrectBitwiseOperations`**  
    🔢 Identifies incorrect usage of bitwise operators.

20. **`checkIncorrectFloatingPointHandling`**  
    🎯 Flags potential issues with floating-point precision.

21. **`checkIncorrectStatefulLogic`**  
    🔄 Detects incorrect logic in stateful operations.

---

## 🚀 How to Use

1. Clone the repository:
   ```bash
   git clone https://github.com/ShubhamYadav25/ScanSense.git

---

## 🚀 Example Output

```plaintext
Line 3: Potential incorrect comparison operator (use == instead of =)
Line 7: Switch statement missing default case
Line 12: Function may not return a value on all paths

## 🛠️ Future Work

- 🌟 Add support for more advanced error detection using Abstract Syntax Tree (AST).
- 🤖 Integrate with CI/CD pipelines for automated code analysis.
- 🌍 Extend to support other programming languages.

---

## 🤝 Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request.

---

## 📄 License

This project is licensed under the MIT License. See [LICENSE](./LICENSE) for details.
