CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) utaxi.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/utaxi_server.o: server/utaxi_server.cpp server/handlers.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp backend/location.hpp backend/interface.hpp backend/const.hpp backend/exceptions.hpp
	$(CC) $(CF) -c server/utaxi_server.cpp -o $(BUILD_DIR)/utaxi_server.o
    
$(BUILD_DIR)/handlers.o: server/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp backend/interface.hpp backend/location.hpp
	$(CC) $(CF) -c server/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/exceptions.o: backend/exceptions.cpp backend/exceptions.hpp
	$(CC) $(CF) -c backend/exceptions.cpp -o $(BUILD_DIR)/exceptions.o

$(BUILD_DIR)/consts.o: backend/const.cpp backend/const.hpp
	$(CC) $(CF) -c backend/const.cpp -o $(BUILD_DIR)/const.o

$(BUILD_DIR)/person.o: backend/person.hpp backend/person.cpp backend/trip.hpp backend/exceptions.hpp
	$(CC) $(CF) -c backend/person.cpp -o $(BUILD_DIR)/person.o

$(BUILD_DIR)/passenger.o: backend/passenger.hpp backend/passenger.cpp backend/person.hpp backend/const.hpp backend/trip.hpp backend/exceptions.hpp
	$(CC) $(CF) -c backend/passenger.cpp -o $(BUILD_DIR)/passenger.o

$(BUILD_DIR)/driver.o: backend/driver.hpp backend/driver.cpp backend/person.hpp backend/const.hpp backend/trip.hpp backend/exceptions.hpp
	$(CC) $(CF) -c backend/driver.cpp -o $(BUILD_DIR)/driver.o

$(BUILD_DIR)/trip.o: backend/trip.hpp backend/trip.cpp backend/location.hpp backend/const.hpp backend/person.hpp backend/passenger.hpp backend/driver.hpp backend/exceptions.hpp
	$(CC) $(CF) -c backend/trip.cpp -o $(BUILD_DIR)/trip.o

$(BUILD_DIR)/location.o: backend/location.hpp backend/location.cpp backend/exceptions.hpp
	$(CC) $(CF) -c backend/location.cpp -o $(BUILD_DIR)/location.o

$(BUILD_DIR)/interface.o: backend/interface.hpp backend/interface.cpp backend/const.hpp backend/driver.hpp backend/passenger.hpp backend/person.hpp backend/trip.hpp backend/location.hpp backend/exceptions.hpp server/server.hpp
	$(CC) $(CF) -c backend/interface.cpp -o $(BUILD_DIR)/interface.o

$(BUILD_DIR)/main.o: server/main.cpp server/utaxi_server.hpp
	$(CC) $(CF) -c server/main.cpp -o $(BUILD_DIR)/main.o

utaxi.out: $(BUILD_DIR)/main.o  $(BUILD_DIR)/person.o  $(BUILD_DIR)/passenger.o $(BUILD_DIR)/trip.o $(BUILD_DIR)/location.o $(BUILD_DIR)/interface.o $(BUILD_DIR)/driver.o $(BUILD_DIR)/exceptions.o $(BUILD_DIR)/utaxi_server.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o
	$(CC) $(CF) $(BUILD_DIR)/main.o $(BUILD_DIR)/person.o $(BUILD_DIR)/passenger.o $(BUILD_DIR)/trip.o $(BUILD_DIR)/location.o $(BUILD_DIR)/interface.o $(BUILD_DIR)/driver.o $(BUILD_DIR)/exceptions.o $(BUILD_DIR)/utaxi_server.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o -o utaxi.out

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null