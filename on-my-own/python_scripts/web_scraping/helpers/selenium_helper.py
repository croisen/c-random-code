

from typing import Optional, Any, Union, List

from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options

from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.common.by import By
from selenium.webdriver import DesiredCapabilities
from selenium.webdriver.common.proxy import Proxy, ProxyType
from selenium.webdriver.remote.webelement import WebElement

from webdriver_manager.chrome import ChromeDriverManager

import sys
import time

class Browser:
    def __init__(self, path: str, use_tor: bool = False, headless: bool = False):
        self.options: Options = Options()
        self.options.add_argument("--disable-extensions")
        self.options.add_argument("disable-inforbars")
        self.options.add_experimental_option("excludeSwitches", ['enable-automation'])

        if use_tor:
            self.options.add_argument("--proxy-server=socks5://localhost:9050")
        if headless:
            self.options.add_argument("--headless")

        self.driver_manager = ChromeDriverManager(path = path)
        self.service: Service = Service(self.driver_manager.install())
        self.driver = webdriver.Chrome(service = self.service, options = self.options)

    @staticmethod
    def sleep(seconds: int) -> None:
        for i in reversed(range(seconds)):
            try:
                print(f"\rCurrently sleeping, wait for {i:03} seconds", end = "")
                time.sleep(1)
            except KeyboardInterrupt:
                print("\n")
                sys.exit(0)

        print()

    def minimize_browser(self) -> None:
        self.driver.minimize_window()

    def maximize_browser(self) -> None:
        self.driver.maximize_window()

    def close_browser(self) -> None:
        self.driver.quit()

    def make_action(self) -> ActionChains:
        return ActionChains(self.driver)

    def visit_site(self, url: str) -> None:
        self.driver.get(url)

    def scroll_page(self, amount: int) -> None:
        ActionChains(self.driver)\
        .scroll_by_amount(0, amount)\
        .perform()

    def get_elements(self, element_type: Optional[str] = By.ID, value: Optional[str] = None) -> List[WebElement]:
        return self.driver.find_elements(element_type, value)
