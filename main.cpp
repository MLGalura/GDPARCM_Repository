#include <iostream>
#include "BaseRunner.h"

int main() {
	BaseRunner* runner = BaseRunner::getInstance();
	runner->run();
}