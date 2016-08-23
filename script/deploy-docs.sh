#!/bin/bash
git config user.name "Paul Visscher"
git config user.email "p.e.visscher@zefiros.eu"
git remote add gh-token "https://${GH_TOKEN}@github.com/Zefiros-Software/BSPLib.git";
git fetch gh-token && git fetch gh-token gh-pages:gh-pages;
~/zpm-anaconda/bin/mkdocs gh-deploy -v --clean --remote-name gh-token;