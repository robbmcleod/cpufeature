Releasing CPUFeature
====================

* Author: Robert A. McLeod
* Contact: robbmcleod@gmail.com
* Date: 2020-12-28

Following are notes for releasing CPUFeature.

Preliminaries
-------------

* Make sure that the release notes in `README.md` are up to date with the latest news in the release.
* Make sure that the `branch` variable in `setup.py` is `''` rather than `'devN'`.
* Do a build to ensure that `cpufeature/version.py` is correct:

    `python setup.py build`

* Do a commit and a push:

    `git commit -a -m "Getting ready for release X.Y.Z"`

* If the directories `dist` or `artifact` exist, delete them.

Tagging
-------

* Create a tag `vX.Y.Z` from `master` and push the tag to GitHub:

    `git tag -a vX.Y.Z -m "Tagging version X.Y.Z"`
    `git push`
    `git push --tags`

* If you happen to have to delete the tag, such as artifacts demonstrates a fault, first delete it locally,

    `git tag --delete vX.Y.Z`

  and then remotely on Github,

    `git push --delete origin vX.Y.Z`

Build Wheels
------------

* Check on GitHub Actions `github.com/robbmcleod/cpufeature/actions` that all the wheels built successfully.
* Download `artifacts.zip` and unzip.
* Make the source tarball with the command

    `python setup.py sdist`

Releasing
---------

* Upload the built wheels to PyPi via Twine.

    `twine upload artifact/cpufeature*.whl`

* Upload the source distribution.

    `twine upload dist/cpufeature-X.Y.Z.tar.gz`

* Check on `pypi.org/project/cpufeature/#files` that the wheels and source have uploaded as expected.

Announcing
----------

* Send an announcement to the NumPy list, PyData and python-announce
  list.  Use the `ANNOUNCE.md` file as skeleton (or possibly as the
  definitive version).

Post-release Actions
--------------------

* Version bump in `setup.py`, e.g. `X.Y.Z` -> `X.Y.(Z+1).dev0`.
* Create new headers for adding features in `README.md`. The first bullet point should be `* **Under development.**`
* Commit these changes

    `git commit -a -m "Post X.Y.Z release actions done"`
    `git push`

* Clean `artifact` and `dist` directories.

    `rm artifact/*.whl`
    `rm dist/*.tar.gz`

Fin.
