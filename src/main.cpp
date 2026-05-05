#include <iostream>
#include <vector>
#include <limits>

float readFloat() {
    float value;
    while (true) {
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите число: ";
        } else {
            return value;
        }
    }
}
int main() {
	int n;
	std::vector<std::vector<float>> matrix;
	std::cout<<"enter size of matrix"<<std::endl;
	std::cin>>n;
	matrix.resize(n);
	for (int i{0}; i < n; i++) {
		matrix[i].resize(n);
		}
	std::cout<<"enter elements of matrix using spaces"<<std::endl;
	for (int i{0}; i < n; i++) {
		for (int j{0}; j < n; j++) {
			matrix[i][j] = readFloat();
			}
		}
	std::cout<<"your matrix:"<<std::endl;
	for (int i{0}; i < n; i++) {
		for (int j{0}; j < n; j++) {
			std::cout<<matrix[i][j]<<" ";
			}
		std::cout<<std::endl;
		}
}