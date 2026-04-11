# This program enumarates all the http headers from a website 

import pyfiglet
import requests
import validators
from datetime import datetime

# User menu
def user_menu():
    ascii_banner = pyfiglet.figlet_format("What The Header!")
    print("=" * 50)
    print(ascii_banner)
    print("=" * 50)
    print("| Enter a valid URL and find out WTH |")
    print("=" * 50)

    # Get user input
    URL = input("URL: ")

    # Check if user input is valid
    if is_valid_url(URL):
        # Return URL if vaild
        return URL
    else:
        # Exit Program
        print("Invalid URL")
        exit()

def make_request(URL):
    try:
        # Make Get Request to given URL
          req = requests.get(URL)
    except (ConnectionError, request.HTTPError, ConnectionTimeout):
        # Raise No Connection, Timeout Errors when no connection or timeout
        # HTTPError raises exception for 400, 500 response codes
        print('Connection Error:\nTry:\n1. Check Your Internet Connection\n2. Possible 400, 500 Code Try again another time')
    else:
        # Response body now stored in req
        return req
    finally:

        # Display the final status code
        print('Return Status Code:', req.status_code, end="\n")


def get_headers(responseBody):
    # Print Out the Headers
    print("======================================\n|               Headers              |\n======================================")
    for headers in responseBody.headers:
        print(headers)


def is_valid_url(URL):
    # Check if the Provide URL is valid
    validation = validators.url(URL)

    if validation:
        return True
    else:
        return False

def main():
    # main function entry points
    URL = user_menu()
    get_headers(make_request(URL))


if __name__ == "__main__":
    main()
