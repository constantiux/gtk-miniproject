# How-To Guide

A comprehensive guide to use this repl.

### First time here?

**Skip** this step if you are continuing your work.

Before you begin, make sure you have a Github account, and a Repl.it account. Those are the basic prerequisites.

1. In the `repl.it` terminal, do each

	curl $REPLIT_DB_URL -d 'gitemail=value1'
	curl $REPLIT_DB_URL -d 'gitname=value2'
	curl $REPLIT_DB_URL -d 'gitauth=value3'

 where

 - `value1` is your Github email
 - `value2` is your Github username
 - `value3` is your _personal access token_. Learn more how to make one [here](https://docs.github.com/en/free-pro-team@latest/github/authenticating-to-github/creating-a-personal-access-token)

2. Create your first Github repo (either public or private), and get the repo url _e.g._ `https://github.com/your-username/example-repo-name.git`


3. In the Repl.it terminal, run the following

		git init
		git branch -M main
		git remote add origin https://github.com/your-username/example-repo-name.git


### Resuming your work

For every time you come back to this `repl`, you need to run `init` by **executing** `./init` in the `repl.it` _terminal_.

After changing any file, and ready to test on the `linux03` server, then only need to execute

	git add .
	git commit -m "update"
	git push -u origin main