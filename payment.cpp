#include "payment.h"

#include <fstream>
#include <string>
#include <vector>

using namespace std::string_view_literals;

Payment::Payment() {
    ProceedInput();
}

void Payment::ProceedInput() {
    std::fstream file("meters_data.txt", std::ios::in | std::ios::out | std::ios::app);
    if (!file) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        exit(1);
    }
    while (file) {
        file >> water_meter_prev_ >> gas_meter_prev_ >> light_meter_prev_;
    }
    file.close();

    SetData();
    SetMeters();

    file.open("meters_data.txt", std::ios::in | std::ios::out);
    if (!file) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        exit(1);
    }
    file << water_meter_ << ' ' << gas_meter_ << ' ' << light_meter_;
    file.close();
}

double Payment::CalculateCostWater() {
    return (water_meter_ - water_meter_prev_) * TARIF_WATER;
}

double Payment::CalculateCostGas() {
    return (gas_meter_ - gas_meter_prev_) * TARIF_GAS;
}

double Payment::CalculateCostLight() {
    int difference = light_meter_ - light_meter_prev_;
    if (difference <= 150) return difference * TARIF_LIGHT_150;
    else return (150 * TARIF_LIGHT_150) + (difference - 150) * TARIF_LIGHT_800;
}

double Payment::CalculateCostRent() {
    return TARIF_RENT;
}

double Payment::CalculateCostGarbage() {
    return TARIF_GARBAGE;
}

int Payment::IsInt(int number) {
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "введите ЦЕЛОЕ число: ";
        std::cin >> number;
    }
    return number;
}

void Payment::SetData() {
    std::cout << "Введите месяц и год оплаты (MM ГГ): "sv;
    std::cin >> date_.month;
    IsInt(date_.month);
    std::cin >> date_.year;
    IsInt(date_.year);
}

void Payment::SetMeters() {
    std::cout << "Введите показания приборов учёта"sv << std::endl;
    std::cout << "вода: "sv;
    std::cin >> water_meter_;
    IsInt(water_meter_);
    std::cout << "газ: "sv;
    std::cin >> gas_meter_;
    IsInt(gas_meter_);
    std::cout << "свет: "sv;
    std::cin >> light_meter_;
    IsInt(light_meter_);
}

const Date& Payment::GetDate() const {
    return date_;
}

const std::pair<int, int> Payment::GetWaterMeters() const {
    return { water_meter_, water_meter_prev_ };
}

const std::pair<int, int> Payment::GetGasMeters() const {
    return { gas_meter_, gas_meter_prev_ };
}

const std::pair<int, int> Payment::GetLightMeters() const {
    return { light_meter_, light_meter_prev_ };
}
