Supported for linux. <br/>
Install firefox. <br/>
`sudo apt install firefox` <br/>
-Install geckodriver <br/>
`wget https://github.com/mozilla/geckodriver/releases/download/v0.31.0/geckodriver-v0.31.0-linux32.tar.gz` <br/>
`tar -xvzf geckodriver*` <br/>
`chmod +x geckodriver` <br/>
`sudo mv geckodriver /usr/local/bin/` <br/>
-Install requirements <br/>
`pip install -r requirements.txt` <br/>
-Run <br/>
`python3 app.py`

If you get an error "Firefox profile is missing or inaccesible, this is because firefox is installed using snap. Follow the steps in this link https://www.omgubuntu.co.uk/2022/04/how-to-install-firefox-deb-apt-ubuntu-22-04#:%7E:text=Installing%20Firefox%20via%20Apt%20(Not%20Snap)&text=You%20add%20the%20Mozilla%20Team,%2C%20bookmarks%2C%20and%20other%20data. to reinstall firefox and it should work.
