#include <stdio.h>
#include <stdint.h>

// CRC-16 polynomial: x^16 + x^15 + x^2 + 1 (0x8005)
#define CRC16_POLYNOMIAL 0x8005

uint16_t calculate_crc16(uint8_t *data, size_t length) {
    uint16_t crc = 0; // Initialize CRC value
    
    // Process each byte of data
    for (size_t i = 0; i < length; i++) {
        crc ^= (data[i] << 8); // XOR the byte with the high byte of CRC
        
        // Process each bit of the byte
        for (int j = 0; j < 8; j++) {
            if (crc & 0x8000) {
                // If MSB is 1, shift and XOR with polynomial
                crc = (crc << 1) ^ CRC16_POLYNOMIAL;
            } else {
                // If MSB is 0, just shift
                crc <<= 1;
            }
        }
    }
    
    return crc;
}

int main() {
    // Example input data (255 bytes)
    uint8_t data[255];
    
    // Initialize example data (you can modify this as needed)
    for (int i = 0; i < 255; i++) {
        data[i] = i; // Just filling with sequential numbers for demonstration
    }
    
    // Calculate CRC-16
    uint16_t crc = calculate_crc16(data, sizeof(data));
    
    // Print the result in hexadecimal
    printf("CRC-16 value: 0x%04X\n", crc);
    
    return 0;
}
