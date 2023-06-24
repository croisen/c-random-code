#!/home/linuxbrew/.linuxbrew/bin/py


from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.common.by import By
from webdriver_manager.chrome import ChromeDriverManager
import time

class Browser:
    def __init__(self):
        self.options: Options = Options()
        self.options.add_argument("--start-maximized")
        self.options.add_experimental_option("excludeSwitches", ['enable-automation'])

        self.service: Service = Service(ChromeDriverManager(path = r"drivers/").install())
        self.service.args = "--log-level=ALL"

        self.driver = webdriver.Chrome(service = self.service, options = self.options)

    def visit_site(self, url: str) -> None:
        self.driver.get(url)

    def close_browser(self) -> None:
        self.driver.quit()

    def make_action(self) -> ActionChains:
        return ActionChains(self.driver)

    def scroll_page(self, amount: int) -> None:
        ActionChains(self.driver)\
        .scroll_by_amount(0, amount)\
        .perform()

if __name__ == "__main__":
    while True:
        browser = Browser()
        browser.visit_site("https://sites.google.com/view/croisen/home")
        browser.scroll_page(6000)
        time.sleep(10)
        browser.close_browser()
