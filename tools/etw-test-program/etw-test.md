# ETW Test Provider

A small Windows program to learn how ETW works.

It registers a TraceLogging provider and emits an event when a button is pressed.

## Provider GUID

    8f5c2e71-4a63-4c92-9137-5ea48b21d6f0

## How to use

1. Build the project.
2. Open TraceView as Administrator.
3. Create a new log session and add the provider by GUID.
4. Start the session.
5. Run the program and click OK or ERROR.
6. Events show up in TraceView.

## Notes

- This is a learning tool, not part of SignStrike.
- Requires Administrator rights for TraceView, not for the program itself.
