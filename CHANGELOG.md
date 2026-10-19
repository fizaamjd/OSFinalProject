# Changelog

## Unreleased

- Restore Calculator as a four-operation GTK utility; historical Calculator.c contained an incomplete second shell implementation. Validate numeric inputs, division by zero and non-finite results.
- Correct the clock timer callback signature and bounded timezone formatting.

- Replace duplicated file-manager code in Notepad.c with a GTK UTF-8 editor, open/save dialogs, overwrite confirmation and error feedback. The original 2024 demo is historical footage, not a recording of this maintenance revision.
- Include the missing string header for the clock utility.

- Add project-specific setup, architecture and verification documentation.
- Add contribution, conduct, support and private security-reporting guidance.
- Add issue forms, pull request guidance and automated checks.

Original project history remains in Git. No new benchmark result is claimed.
