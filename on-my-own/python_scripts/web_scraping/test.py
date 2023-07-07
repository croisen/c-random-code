#!/usr/bin/env python3


import random
import subprocess
import time

import helpers.selenium_helper as sh

if __name__ == "__main__":
    browser = sh.Browser(path = r"drivers/", use_tor = True, headless = True)
    browser.visit_site("https://sites.google.com/view/banzon")
    browser.sleep(random.randint(2, 80))

    while True:
        browser.scroll_page(random.randint(200, 450))
        choice =  random.choice(browser.get_elements(sh.By.XPATH, "//a"))

        while not all([choice.is_displayed(),
                       choice.is_enabled(),
                       choice.get_property('href').startswith("https://sites.google.com"),
                       choice.get_property('href') != browser.driver.current_url]):
            choice =  random.choice(browser.get_elements(sh.By.XPATH, "//a"))

        browser.sleep(10)
        print(f"Now visiting: {choice.get_property('href')}")
        choice.click()
        browser.sleep(random.randint(20, 60))
        browser.scroll_page(random.randint(200, 350) * (-1))

        if random.randint(0, 7) == 7:
            print("Loop done, closing browser, starting new iteration...")
            break

    browser.sleep(5)
    browser.visit_site("https://sites.google.com/view/croisen")
    browser.sleep(random.randint(2, 44))

    while True:
        browser.scroll_page(random.randint(200, 450))
        choice =  random.choice(browser.get_elements(sh.By.XPATH, "//a"))

        while not all([choice.is_displayed(),
                       choice.is_enabled(),
                       choice.get_property('href').startswith("https://sites.google.com"),
                       choice.get_property('href') != browser.driver.current_url]):
            choice =  random.choice(browser.get_elements(sh.By.XPATH, "//a"))

        browser.sleep(random.randint(10, 45))
        print(f"Now visiting: {choice.get_property('href')}")
        choice.click()
        browser.sleep(random.randint(17, 33))
        browser.scroll_page(random.randint(200, 350) * (-1))

        if random.randint(0, 7) == 7:
            print("Loop done, closing browser, starting new iteration...")
            break

    browser.close_browser()
