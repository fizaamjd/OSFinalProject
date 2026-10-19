# Security policy

The maintained source branch is main. Report vulnerabilities through [private reporting](https://github.com/fizaamjd/OSFinalProject/security/advisories/new), using a sanitized reproduction. No response-time guarantee or independent security audit is claimed.

The process cancellation UI invokes pkexec and can terminate real host processes. File utilities modify real files. Resource quotas are simulated, task tracking is bounded and input validation is incomplete. Run only in a disposable VM under an ordinary user account, using your own test processes. UI modes do not grant kernel privilege.
