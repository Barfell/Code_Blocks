import flask             #import web framework
import datetime      #import time library to read current time
import RPi.GPIO     #RPi GPIO library

app=flask.Flask(__name__)

#home page
@app.route("/")
def hello():
    time=datetime.datetime.now()       #get current time
    timeString=time.strftime("%H:%M %d-%m-%Y")     #get current time in a nice format
    templateData={'title': 'Pi GPIO Input Test', 'time': timeString}      #dictionary used to send data to html file
    return flask.render_template('time.html', **templateData)     #send time data in the html template described in time.html

#read input pins    
@app.route("/pinStat/<pin>")
def readPin(pin):
    try:
        RPi.GPIO.setmode(RPi.GPIO.BCM)        #use Broadcom notation
        RPi.GPIO.setup(int(pin), RPi.GPIO.IN)        #set pin as input
        if RPi.GPIO.input(int(pin))==True:               #check pin state
            response="Pin Number "+pin+" is HIGH"
        else:
            response="Pin Number "+pin+" is LOW"
            
    except:
        response="Pin Number "+pin+" Cannot Be Read"
        
    templateData={'title': 'Pi GPIO Input Status', 'response': response}        #dictionary used to send data to html file
    return flask.render_template('gpio_input.html', **templateData)     #send GPIO data in the html template described in gpio_input.html

#if script was run directly from command line, have the server listen in on port 80 and report errrors    
if __name__== "__main__":
    app.run(host='0.0.0.0', port=80, debug=True)
