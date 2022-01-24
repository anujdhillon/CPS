from flask import Flask, request, jsonify, send_from_directory
from flask_sock import Sock
from flask_cors import CORS
import datetime
import os
import logging
from time import sleep
from selenium import webdriver
import random
import json
from selenium.webdriver.support.ui import WebDriverWait,  Select
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
from selenium.common.exceptions import TimeoutException
from subprocess import run, Popen, PIPE
from flask_socketio import SocketIO
import requests
app = Flask(__name__, static_url_path='', static_folder='build')
CORS(app, supports_credentials=True)
# log = logging.getLogger('werkzeug')
# log.disabled = True
sock = Sock(app)
contest = None
base_dir = os.path.join(os.path.dirname(
    os.path.realpath(__file__)), "files")


class Contest:
    def __init__(self, username, password, platform):
        self.username = username
        self.password = password
        self.platform = platform
        self.contest_id = None
        options = webdriver.firefox.options.Options()
        options.add_argument("--headless")
        self.driver = webdriver.Firefox(options=options)
        if platform == "codeforces":
            self.driver.get(
                f"https://codeforces.com/enter?back=%2F")
            print("Site opened.")
            self.driver.find_element(By.ID,
                                     "handleOrEmail").send_keys(username)
            self.driver.find_element(
                By.ID, "password").send_keys(password)
            self.driver.find_element(By.CLASS_NAME, "submit").click()
        elif platform == "practice":
            pass
        elif platform == "atcoder":
            self.driver.get(
                f"https://atcoder.jp/login?continue=https%3A%2F%2Fatcoder.jp%2F")
            self.driver.find_element(
                By.ID, "username").send_keys(username)
            self.driver.find_element(
                By.ID, "password").send_keys(password)
            self.driver.find_element(By.ID, "submit").click()
        self.problem_list = []
        self.problem_details = {}

    def start_contest(self, contest_id):
        self.contest_id = contest_id
        self.contest_dir = os.path.join(
            base_dir, f"{self.platform}_{self.contest_id}")
        test_cases = os.path.join(self.contest_dir, "testcases.json")
        if not os.path.exists(self.contest_dir):
            os.system(f"mkdir {self.contest_dir}")
            with open(test_cases, 'w') as f:
                f.write(str({}))
        with open(test_cases) as f:
            self.problem_details = json.loads(f.read())
        if self.platform == "codeforces":
            self.driver.get(
                f"https://codeforces.com/contest/{self.contest_id}")
            self.problem_list = [item.find_element(By.TAG_NAME,
                                                   "a").text for item in self.driver.find_elements(By.CLASS_NAME, "id")]
        elif self.platform == "practice":
            self.problem_list = ["A", "B", "C", "D"]
            for p in self.problem_list:
                self.problem_details[p] = {"test_cases": [{"input": "", "output": "",
                                                           "result": "", "verdict": "", "comments": ""}]}
        elif self.platform == "atcoder":
            count = 1
            url = f"https://atcoder.jp/contests/{self.contest_id}/tasks"
            self.driver.get(url)
            print(self.driver.current_url)
            while True:
                try:
                    p_id = self.driver.find_element(
                        By.XPATH, f"/html/body/div[3]/div/div[1]/div[2]/div/table/tbody/tr[{count}]/td[1]/a").text
                    count += 1
                except Exception as e:
                    print(e)
                    break
            for i in range(count-1):
                self.problem_list.append(chr(ord('A') + i))
        print(self.problem_list)

    def get_problem_details(self, problem_id):
        if problem_id in self.problem_details:
            return self.problem_details
        print(f"Parsing test cases for problem {problem_id}")
        if self.platform == "codeforces":
            self.driver.get(
                f"https://codeforces.com/contest/{self.contest_id}/problem/{problem_id}")
            test_cases = [{"input": "", "output": "",
                           "result": "", "verdict": "", "comments": ""}]
            input_txts = self.driver.find_elements(
                By.CLASS_NAME, "input")
            output_txts = self.driver.find_elements(
                By.CLASS_NAME, "output")
            for j in range(len(input_txts)):
                test_cases.append({"input": input_txts[j].find_element(By.TAG_NAME,
                                                                       "pre").text, "output": output_txts[j].find_element(By.TAG_NAME, "pre").text, "result": "", "verdict": "", "comments": ""})
            self.problem_details[problem_id] = {
                "test_cases": test_cases,
            }
        if self.platform == "atcoder":
            self.problem_details[problem_id] = {}
            self.problem_details[problem_id]["test_cases"] = [{"input": "", "output": "",
                                                               "result": "", "verdict": "", "comments": ""}]
            self.driver.get(
                f"https://atcoder.jp/contests/{self.contest_id}/tasks/{self.contest_id}_{problem_id}")
            count, started, index = 1, 0, 1
            while True:
                try:
                    data = self.driver.find_element(
                        By.ID, f"pre-sample{count}").text
                    if data:
                        if count % 2 == 0:
                            self.problem_details[problem_id]["test_cases"].append({"input": "", "output": "",
                                                                                   "result": "", "verdict": "", "comments": ""})
                            self.problem_details[problem_id]["test_cases"][index]["input"] = data
                        else:
                            self.problem_details[problem_id]["test_cases"][index]["output"] = data
                            index += 1
                        started = 1
                except:
                    if started:
                        break
                count += 1
        with open(f"{self.contest_dir}/testcases.json", 'w') as f:
            json.dump(self.problem_details, f)
        return self.problem_details

    def submit(self, problem_id, file_loc):
        if self.platform == "codeforces":
            self.driver.get(
                f"https://codeforces.com/contest/{self.contest_id}/submit/{problem_id}")
            self.driver.find_element(By.NAME, "sourceFile").send_keys(file_loc)
            self.driver.find_element(By.CLASS_NAME, "submit").click()
        elif self.platform == "practice":
            pass
        elif self.platform == "atcoder":
            self.driver.get(
                f"https://atcoder.jp/contests/{self.contest_id}/submit?taskScreenName={self.contest_id}_{problem_id}")
            # to-do

    def stats(self):
        res = {}
        try:
            if self.platform == "codeforces":
                self.driver.get(
                    f"https://codeforces.com/contest/{self.contest_id}")
                for i in range(len(self.problem_list)):
                    k = str(i+2)
                    res[self.problem_list[i]] = self.driver.find_element(
                        By.XPATH, "/html/body/div[6]/div[4]/div[2]/div[2]/div[6]/table/tbody/tr["+k+"]/td[4]/a").text
            elif self.platform == "practice":
                pass
            elif self.platform == "atcoder":
                self.driver.get(
                    f"https://atcoder.jp/contests/{self.contest_id}/standings")
                WebDriverWait(self.driver, 6).until(
                    EC.presence_of_element_located((By.CLASS_NAME, 'standings-statistics')))
                standings = self.driver.find_element(
                    By.CLASS_NAME, "standings-statistics")
                acs = [num.text for num in standings.find_elements(
                    By.CLASS_NAME, "standings-ac")]
                acs = acs[1:]
                for i in range(len(self.problem_list)):
                    res[self.problem_list[i]] = acs[i]
        except Exception as e:
            print("Failed to fetch stats.", str(e))
        return str(res)

    def submissions(self):
        res = {}
        if self.platform == "codeforces":
            api_url = f"https://codeforces.com/api/contest.status?contestId={self.contest_id}&from=1&count=3&handle={self.username}"
            data = json.loads(requests.get(api_url).text)
            res = [{"problemId": sub['problem']['index'], "verdict": sub['verdict'],
                    "testsPassed": sub['passedTestCount'], "time": sub["creationTimeSeconds"]} for sub in data['result']]
        elif self.platform == "practice":
            pass
        elif self.platform == "atcoder":
            self.driver.get(
                f"https://atcoder.jp/contests/{self.contest_id}/submissions?f.Task=&f.LanguageName=&f.Status=&f.User={self.username}")
            res = []
            for i in range(1, 4):
                try:
                    data = {"testsPassed": "unknown"}
                    data["time"] = self.driver.find_element(
                        By.XPATH, f"/html/body/div[3]/div/div[1]/div[3]/div[1]/div[2]/table/tbody/tr[{str(i)}]/td[1]/time").text
                    data["verdict"] = self.driver.find_element(
                        By.XPATH, f"/html/body/div[3]/div/div[1]/div[3]/div[1]/div[2]/table/tbody/tr[{str(i)}]/td[7]/span").text
                    data["problemId"] = self.driver.find_element(
                        By.XPATH, f"/html/body/div[3]/div/div[1]/div[3]/div[1]/div[2]/table/tbody/tr[{str(i)}]/td[2]/a").text
                    if data["verdict"] == "AC":
                        data["verdict"] = "OK"
                    res.append(data)
                except Exception as e:
                    print(e)
                    break
        return res


@app.route('/')
def index():
    return send_from_directory(app.static_folder, 'index.html')


@app.route('/standings')
def standings():
    res = {}
    if contest and contest.contest_id:
        res["stats"] = contest.stats()
    else:
        res["stats"] = "No contest found."
    return json.dumps(res)


@app.route('/submissions')
def submissions():
    res = {}
    if contest and contest.contest_id:
        res["submissions"] = contest.submissions()
    else:
        res["submissions"] = []
    return json.dumps(res)


def check(s1, s2):
    if s1.split() == s2.split():
        return "AC"
    else:
        return "WA"


@app.route('/login/<platform>/<username>/<password>')
def login(platform, username, password):
    global contest
    contest = Contest(username, password, platform)
    return jsonify({"status": "Logged in"})


@app.route('/start/<contest_id>')
def start(contest_id):
    global contest
    contest.start_contest(contest_id)
    return jsonify({"problemList": contest.problem_list})


@app.route('/change/<problem_id>')
def change(problem_id):
    global contest
    print(f"Changing to problem {problem_id}.")
    file_loc = os.path.join(contest.contest_dir, f"{problem_id}.cpp")
    if not os.path.exists(file_loc):
        print("File not found. Creating a new file.")
        with open("boilerplate/template.cpp") as f:
            template = f.read()
        with open(file_loc, 'w') as f:
            f.write(template)
    os.system(f"code -g --goto {file_loc}:42:4")
    return jsonify({"problemDetails": contest.get_problem_details(problem_id)})


@app.route('/compile/<problem_id>')
def compile(problem_id):
    global contest
    file_loc = os.path.join(contest.contest_dir, f"{problem_id}.cpp")
    command = f"g++ -std=c++17 -g -Wall -Wextra -pedantic -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector  {file_loc} -o {file_loc}.exe".split(
    )
    process = Popen(
        command, stdout=PIPE, stderr=PIPE, encoding='UTF-8')
    err = process.communicate()[1]
    if not err:
        err = "Compiled successfully."
    return err


@app.route('/run/<problem_id>', methods=["POST"])
def run(problem_id):
    global contest
    test_case = request.json["testCase"]
    file_loc = os.path.join(contest.contest_dir, f"{problem_id}.cpp.exe")
    if not os.path.exists(file_loc):
        verdict = "Executable not found. Try compiling again."
        out = ""
        err = ""
    elif not test_case["input"]:
        verdict = "No input."
        out = ""
        err = ""
    else:
        command = f"{file_loc}"
        process = Popen([command], stdout=PIPE, stdin=PIPE,
                        stderr=PIPE, encoding='UTF-8')
        process.stdin.write(test_case["input"])
        try:
            out, err = process.communicate(timeout=5)
            if out == None:
                out = ""
            if err == None:
                err = ""
            verdict = check(out, test_case["output"])
        except:
            process.kill()
            out = ""
            err = ""
            verdict = "TLE"
    return jsonify({"verdict": verdict, "result": out, "comments": err})


@app.route("/submit/<problem_id>")
def submit(problem_id):
    file_loc = os.path.join(contest.contest_dir, f"{problem_id}.cpp")
    contest.submit(problem_id, file_loc)
    print("Code submitted. Fingers crossed.")
    return "Success"


if (__name__ == "__main__"):
    app.run(debug=True)
