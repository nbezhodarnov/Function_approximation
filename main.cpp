#include <tgmath.h>
#include <iostream>
//#include <iomanip>

long double func(long double x) {
    return 21 * exp(-(1 / 4.0) * pow(x - 2.5, 2)) + 17.2 * exp(-(1 / 6.0) * pow(x - 8, 2));
    //return 0.7 * exp(-(1 / 8.0) * pow(x - 2.3, 2)) + 1.2 * exp(-(1 / 5.0) * pow(x - 6.8, 2));
};

int main()
{
    //std::cout << std::setprecision(33);/
    long double x[1000], f[1000];
    for (int i = 0; i < 1000; ++i) {
        x[i] = i * 0.01;
        f[i] = func(x[i]);
    }



    int index = 100;
    long double a1, a2, b1, b2, c1, c2;
    while ((((f[index + 1] - f[index]) / 0.001 >= 0.5) || ((f[index + 1] - f[index]) / 0.001 > (f[index + 2] - f[index + 1]) / 0.001)) && (f[index] < f[index + 1])) {
        index++;
    }
    c1 = x[index];
    a1 = f[index];
    b1 = -log(f[index * 100 / 245] / a1) / (pow(x[index / 2] - c1, 2));
    index = 900;
    while ((((f[index - 1] - f[index]) / 0.001 >= 0.5) || ((f[index - 1] - f[index]) / 0.001 > (f[index - 2] - f[index - 1]) / 0.001)) && (f[index] < f[index - 1])) {
        index--;
    }
    c2 = x[index];
    a2 = f[index];
    b2 = -log(f[index + (1000 - index) * 100 / 182] / a2) / (pow(x[index + (1000 - index) / 2] - c2, 2));

    bool is_two_extremums = true;
    if (std::abs(c1 - c2) <= 0.001) {
        int index_temp = 999;
        while ((f[index_temp - 1] - f[index_temp]) / 0.001 < 0.5) {
            index_temp--;
        }
        while ((((f[index_temp - 1] - f[index_temp]) / 0.001 >= 0.5) || ((f[index_temp - 1] - f[index_temp]) / 0.001 > (f[index_temp - 2] - f[index_temp - 1]) / 0.001)) && (f[index_temp] < f[index_temp - 1]) && (index_temp > 900)) {
            index_temp--;
        }
        if (index_temp <= 900) {
            index_temp = 0;
            while((f[index_temp + 1] - f[index_temp]) / 0.001 < 0.5) {
                index_temp++;
            }
            while ((((f[index_temp + 1] - f[index_temp]) / 0.001 >= 0.5) || ((f[index_temp + 1] - f[index_temp]) / 0.001 > (f[index_temp + 2] - f[index_temp + 1]) / 0.001)) && (f[index_temp] < f[index_temp + 1]) && (index_temp < 100)) {
                index_temp++;
            }
            if (index_temp >= 100) {
                is_two_extremums = false;
            } else {
                c1 = x[index_temp];
                a1 = f[index_temp];
                b1 = -log(f[index_temp / 2] / a1) / (pow(x[index_temp / 2] - c1, 2));
            }
        } else {
            c2 = x[index_temp];
            a2 = f[index_temp];
            b2 = -log(f[index_temp + (1000 - index_temp) / 2] / a2) / (pow(x[index_temp + (1000 - index_temp) / 2] - c2, 2));
        }
    }



    std::cout << "a1 = " << a1 << ", b1 = " << b1 << ", c1 = " << c1 << '\n';
    if (is_two_extremums) {
        std::cout << "a2 = " << a2 << ", b2 = " << b2 << ", c2 = " << c2 << "\n\n";
    } else {
        a1 /= 2;
        a2 /= 2;
        std::cout << '\n';
    }





    long double step1 = 0.5, step2 = 0.01, step3 = 0.1, min_value = INFINITY, temp;
    if ((a1 > 1000) || (a2 > 1000)) {
        step1 = 2;
        step3 = 0.05;
    } else if ((a1 > 100) || (a2 > 100)) {
        step1 = 1;
        step3 = 0.1;
    } else if ((a1 > 10) || (a2 > 10)) {
        step1 = 0.5;
        step3 = 0.5;
    } else {
        step1 = 0.1;
        step3 = 1;
    }
    if ((b1 > 10) || (b2 > 10)) {
        step2 = 0.5;
    } else if ((b1 > 1) || (b2 > 1)) {
        step2 = 0.05;
    } else {
        step2 = 0.01;
    }
    if (!is_two_extremums) {
        step1 *= 2;
        step2 *= 2;
        step3 *= 2;
    }
    int numbers_of_points = 50, counter = 0;
    uint8_t min_point_indexes[6];
    for (uint8_t i = 0; i < 6; ++i) {
        min_point_indexes[i] = 0;
    }
    bool q = true;
    while (min_value > 0.01) {
    q = false;
    for (uint8_t i = 0; i < 5; ++i) {
        for (uint8_t j = 0; j < 5; ++j) {
            for (uint8_t k = 0; k < 5; ++k) {
                for (uint8_t l = 0; l < 5; ++l) {
                    for (uint8_t m = 0; m < 5; ++m) {
                        for (uint8_t n = 0; n < 5; ++n) {
                            temp = 0;
                            for (int p = 0; p < numbers_of_points; ++p) {
                                temp += std::abs(f[p * 1000 / numbers_of_points] - (a1 - (2 - i) * step1) * exp(-(b1 - (2 - j) * step2) * pow(x[p * 1000 / numbers_of_points] - c1 + (2 - k) * step3, 2)) - (a2 - (2 - l) * step1) * exp(-(b2 - (2 - m) * step2) * pow(x[p * 1000 / numbers_of_points] - c2 + (2 - n) * step3, 2)));
                            }
                            if (temp < min_value) {
                                q = true;
                                min_value = temp;
                                min_point_indexes[0] = i;
                                min_point_indexes[1] = j;
                                min_point_indexes[2] = k;
                                min_point_indexes[3] = l;
                                min_point_indexes[4] = m;
                                min_point_indexes[5] = n;
                            }
                        }
                    }
                }
            }
        }
    }
    if (!q) {
        step1 /= 10;
        step2 /= 10;
        step3 /= 10;
        continue;
    }
    a1 -= (2 - min_point_indexes[0]) * step1;
    b1 -= (2 - min_point_indexes[1]) * step2;
    c1 -= (2 - min_point_indexes[2]) * step3;
    a2 -= (2 - min_point_indexes[3]) * step1;
    b2 -= (2 - min_point_indexes[4]) * step2;
    c2 -= (2 - min_point_indexes[5]) * step3;
    if ((min_point_indexes[0] % 4 != 0) && (min_point_indexes[1] % 4 != 0) && (min_point_indexes[2] % 4 != 0) && (min_point_indexes[3] % 4 != 0) && (min_point_indexes[4] % 4 != 0) && (min_point_indexes[5] % 4 != 0)) {
        step1 /= 10;
        step2 /= 10;
        step3 /= 10;
        //counter = 0;
    } else {
        counter++;
        if ((counter % 10 == 0) && (step2 < 0.01)) {
            step1 = 0.5 * (counter / 10);
            step2 = 0.01 * (counter / 10);
            step3 = 0.1 * (counter / 10);
            //counter = 0;
        }
        if ((counter % 100 == 0) && (min_value > 0.5)) {
            step1 = 0.5;
            step2 = 0.01;
            step3 = 0.1;
            a1 += (rand() % 100 - 50) / 10.0;
            b1 += (rand() % 10 - 5) / 100.0;
            c1 += (rand() % 10 - 5) / 10.0;
            a2 += (rand() % 100 - 50) / 10.0;
            b2 += (rand() % 10 - 5) / 100.0;
            c2 += (rand() % 10 - 5) / 10.0;
            min_value = INFINITY;
            counter = 0;
        }
    }
    std::cout << "a1 = " << a1 << ", b1 = " << b1 << ", c1 = " << c1 << '\n';
    std::cout << "a2 = " << a2 << ", b2 = " << b2 << ", c2 = " << c2 << '\n';
    std::cout << min_value << '\n';

    for (uint8_t i = 0; i < 6; ++i) {
        std::cout << (int)min_point_indexes[i] << ' ';
    }
    std::cout << '\n' << step1 << ' ' << step2 << ' ' << step3 << '\n';
    std::cout << "\n\n";
    }


    std::cout << "a1 = " << a1 << ", b1 = " << b1 << ", c1 = " << c1 << '\n';
    std::cout << "a2 = " << a2 << ", b2 = " << b2 << ", c2 = " << c2 << '\n';

    return 0;
}
