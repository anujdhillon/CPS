Supported for linux.
--> Install firefox.
`sudo apt install firefox`
-Install geckodriver
`wget https://github.com/mozilla/geckodriver/releases/download/v0.24.0/geckodriver-v0.24.0-linux64.tar.gz`
`tar -xvzf geckodriver*`
`chmod +x geckodriver`
`sudo mv geckodriver /usr/local/bin/`
-Install requirements
`pip install -r requirements.txt`
-Run
`python3 app.py`
