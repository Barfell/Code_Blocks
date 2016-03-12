import flask           #import web framework
app=flask.Flask(__name__)      #create a Flask object

#display Hello World!
@app.route("/")                             #run code below when the root URL is accessed       
def hello():
    return "Hello World!"                 #send Hello World text to the client
    
#if script was run directly from command line, have the server listen in on port 80 and report errrors
if __name__ == "__main__":         
    app.run(host='0.0.0.0', port=80, debug=True)
