################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/database.cpp \
../src/get_favourites.cpp \
../src/get_links.cpp \
../src/get_search.cpp \
../src/get_status_profiles.cpp \
../src/jsoncrawler.cpp \
../src/put_links.cpp \
../src/put_statuses_authors.cpp 

OBJS += \
./src/database.o \
./src/get_favourites.o \
./src/get_links.o \
./src/get_search.o \
./src/get_status_profiles.o \
./src/jsoncrawler.o \
./src/put_links.o \
./src/put_statuses_authors.o 

CPP_DEPS += \
./src/database.d \
./src/get_favourites.d \
./src/get_links.d \
./src/get_search.d \
./src/get_status_profiles.d \
./src/jsoncrawler.d \
./src/put_links.d \
./src/put_statuses_authors.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/ktvr5725/thesis/workspace/jsoncpp/jsoncpp/include" -I/opt/boost/boost_1_50_0/include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


