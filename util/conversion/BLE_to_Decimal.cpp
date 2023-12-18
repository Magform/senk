#include <iostream>
#include <string>
#include <vector>

// Function to convert a hexadecimal string into decimal values
std::vector<short> convertHexToDecimal(const std::string& hexString) {
    std::vector<short> decimalValues;

    // Convert each 4-character hexadecimal substring into its corresponding decimal value
    // by reversing the byte order and parsing it from hexadecimal to decimal format.
    for (size_t i = 0; i < hexString.length(); i += 4) {
        std::string hexSubstring = hexString.substr(i, 4);
        std::string reversedHexSubstring = hexSubstring.substr(2, 2) + hexSubstring.substr(0, 2);
        
        short decimalValue = static_cast<short>(std::stoi(reversedHexSubstring, nullptr, 16));
        
        decimalValues.push_back(decimalValue);
    }

    return decimalValues;
}

int main() {
    std::cout << "Enter the BLE data (in hexadecimal format): ";
    std::string bleData;
    std::cin >> bleData;

    std::vector<short> decimalValues = convertHexToDecimal(bleData);
    
    std::cout << "Decimal values:";
    for (const auto& value : decimalValues) {
        std::cout << " " << value;
    }
    std::cout << std::endl;

    return 0;
}