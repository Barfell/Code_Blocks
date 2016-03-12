import requests
from time import sleep

while True:
	json_data=requests.get("http://api.wunderground.com/api/5a08e133d2cfd498/conditions/q/IN/Bengaluru.json")    #get weather data
	weather=json_data.json        #extract data in a hierarchal dictionary

	#display weather data
	print("Time: ", weather["current_observation"]["local_time_rfc822"])
	print("Location: ", weather["current_observation"]["display_location"]["full"])
	print("Longitude: ", weather["current_observation"]["display_location"]["longitude"])
	print("Latitude: ", weather["current_observation"]["display_location"]["latitude"])
	print("Wind: ", weather["current_observation"]["wind_string"])
	print("Temperature: ", weather["current_observation"]["temperature_string"])
	print("Relative Humidity: ", weather["current_observation"]["relative_humidity"])
	print("Weather: ", weather["current_observation"]["weather"])
	sleep(60)
