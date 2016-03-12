import flask             #import web framework
import datetime      #import time library to read current time

app=flask.Flask(__name__)

#display time
@app.route("/")
def hello():
    time=datetime.datetime.now()       #get current time
    timeString=time.strftime("%H:%M %d-%m-%Y")     #get current time in a nice format
    templateData={'title': 'Pi Time Display', 'time': timeString}      #dictionary used to send data to html file
    return flask.render_template('time.html', **templateData)     #send time data in the html template described in time.html

#if script was run directly from command line, have the server listen in on port 80 and report errrors    
if __name__== "__main__":
    app.run(host='0.0.0.0', port=80, debug=True)
