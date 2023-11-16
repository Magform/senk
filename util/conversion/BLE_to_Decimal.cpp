#include <iostream>
#include <string>
#include <vector>

std::vector<short> convertHexToDecimal(const std::string& hexString) {
    std::vector<short> decimalValues;

    for (size_t i = 0; i < hexString.length(); i += 4) {
        // Extract a 4-character hexadecimal substring
        std::string hexSubstring = hexString.substr(i, 4);

        // Reverse the order of the two bytes (little-endian)
        std::string reversedHexSubstring = hexSubstring.substr(2, 2) + hexSubstring.substr(0, 2);

        // Convert the reversed hexadecimal substring to a decimal value
        short decimalValue = static_cast<short>(std::stoi(reversedHexSubstring, nullptr, 16));

        decimalValues.push_back(decimalValue);
    }

    return decimalValues;
}

int main() {
    std::cout << "Enter the BLE data (in hexadecimal format): ";
    std::string bleData;
    std::cin >> bleData;

    // Convert BLE data to decimal values
    std::vector<short> decimalValues = convertHexToDecimal(bleData);

    // Print the decimal values
    std::cout << "Decimal values:";
    for (const auto& value : decimalValues) {
        std::cout << " " << value;
    }
    std::cout << std::endl;

    return 0;
}