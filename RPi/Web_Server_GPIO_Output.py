import flask             #import web framework
import RPi.GPIO     #RPi GPIO library

RPi.GPIO.setmode(RPi.GPIO.BCM)        #use Broadcom notation

#pins being used
pins={17: {"name": "testPin1", "state": RPi.GPIO.LOW}, 27: {"name": "testPin2", "state": RPi.GPIO.LOW}}     

#initialize pins
for pin in pins:
    RPi.GPIO.setup(pin, RPi.GPIO.OUT)
    RPi.GPIO.output(pin, RPi.GPIO.LOW)

app=flask.Flask(__name__)                    #create Flask object

#home page
@app.route("/")
def main():
    for pin in pins:
        pins[pin]["state"]=RPi.GPIO.input(pin)
    templateData={"pins": pins}               #dictionary used to send data to html file    
    return flask.render_template('gpio_output.html', **templateData)     #send GPIO data in the html template described in gpio_output.html

#control output pins     
@app.route("/<changePin>/<action>")
def writePin(changePin, action):
    changePin=int(changePin)
    
    if action=="on":
        RPi.GPIO.output(changePin, RPi.GPIO.HIGH)
        
    if action=="off":
        RPi.GPIO.output(changePin, RPi.GPIO.LOW)
            
    if action=="toggle":
        RPi.GPIO.output(changePin, not RPi.GPIO.input(changePin))
        
    for pin in pins:
        pins[pin]["state"]=RPi.GPIO.input(pin)
        
    templateData={"pins": pins}        #dictionary used to send data to html file
    return flask.render_template('gpio_output.html', **templateData)     #send GPIO data in the html template described in gpio_output.html

#if script was run directly from command line, have the server listen in on port 80 and report errrors    
if __name__== "__main__":
    app.run(host='0.0.0.0', port=80, debug=True)
