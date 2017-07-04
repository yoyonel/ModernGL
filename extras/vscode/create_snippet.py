import json
import sys

text = open(sys.argv[1], 'r').read()
lines = text.replace(' ' * 4, '\t').splitlines() + ['']

snippet = {
	"ModernGL Snippet": {
		"prefix": "mgl_new_example_",
		"body": lines,
    }
}

print(json.dumps(snippet, indent=4))
