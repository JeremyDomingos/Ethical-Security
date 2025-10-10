"""
    Prints the headers of a server response if the status code is 200.
    If the status code is not 200, prints an error message with the status code.
    Handles AttributeError if the response object is invalid.

    Args:
        server_response: The response object returned from a server request. 
            Expected to have 'status_code' and 'headers' attributes.

    Raises:
        None. Handles AttributeError internally and prints an error message.
"""


import requests
import sys

def program_usage():
    """
    Prints required user usage
    """
    print("\t\t~REQUSTER~\n\n===================================================\nPlease Enter A url in the form: https://example.com\n===================================================\n")


def send_request(url_to_query):
    """
    Sends a simple HTTP 1.0 Request
    """
    try:
        response = requests.get(url_to_query)

        return response
    except (requests.exceptions.MissingSchema):
        print(f"Invalid URL: {url_to_query}\n\nSchema missing correct usage.\n")

    

def print_response(server_response):
    """
    Prints response from server
    """
    try:
        if server_response.status_code == 200:
            headers = server_response.headers 
            print("Response Headers:\n")
            for key, value in headers.items():
                print(f"{key}: {value}")
        else:
            print(f"Error with status code of {server_response.status_code}")
    except AttributeError:
        print("ERROR: URL cannot be used to perform request")

def main():
    """
    main application entry point 
    """
    program_usage()

    url_to_query = sys.argv[1] if len(sys.argv) > 1 else "https://www.jeremydomingos.co.za"
    print(f"Querying URL: {url_to_query}\n")

    print_response(send_request(url_to_query))


if __name__ == "__main__":
    main()
