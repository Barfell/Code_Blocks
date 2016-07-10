# Code Blocks
Code Blocks &amp; Examples for Projects

Contains example code and projects for various platforms (mainly embedded).

## Procedure to setup Git on the PC (SSH):

1. Generate and add SSH keys (https://help.github.com/enterprise/2.3/user/articles/generating-an-ssh-key/)

2. Clone the Git repository

    ```
    git clone <your_repository_url>
    ```
  

## Work flow

1. Start playing with your git tools as soon as possible. Here is a [cheat sheet](https://training.github.com/kit/downloads/github-git-cheat-sheet.pdf) with the most important commands. The basic commands for committing your changes are:
    ```
    git add <file_or_folder> # git add -A in case there are new unversioned files
    git commit -m "commit message" 
    git push origin <your_branch> 
    ```

2. When committing your work, it is important to tag each commit with a meaningful message, so that all contributors understand what changes have been made and it is easier to roll-back to earlier revisions in case a mistake has been made. Here is a guide on [how to write better commit messages](https://robots.thoughtbot.com/5-useful-tips-for-a-better-commit-message), so that your repository doesn't end up [like this](https://xkcd.com/1296/).

3. Make use of the [`.gitignore`](http://git-scm.com/docs/gitignore) file. You should never commit intermediate or generated files. The repository should contain only source code and build/automation scripts.

4. Make a habit of branching your work whenever you implement or experiment with new features. Apart from that, each developer in a group should work on her/his own separate branch on different work sets. The `master` branch should contain _final_ or _working_ features. Refer to [this document](https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging) for an overview on the basic principles of branching and merging. 



## Issues & Contributions

Any bug, feature or problem can be managed within a lab group using [the issue tracker](https://guides.github.com/features/issues/). We recommend using it freely on the local repository as means to manage work packages and communicate problems.

If you identify a problem of general interest or related to the provided material you can open an issue on the main (public) repository, which will be visible to all developers. Please take your time and be mindful of what you post in the public domain since it is _really important_ that the issue is correct, concise, and is accompanied by a short description of context in which the issue arose. [Here](https://wiredcraft.com/blog/how-we-write-our-github-issues/) and [here](https://upthemes.com/blog/2014/02/writing-useful-github-issues/) are two discussions in how to write meaningful issues. An issue can be confirmed or invalidated, depending on whether or not it is reproducible.

If you know how to solve an opened issue and would like to contribute to the development of the software, feel free to [fork](https://help.github.com/enterprise/2.4/user/articles/fork-a-repo/) the main repository and [issue a pull request](https://help.github.com/articles/using-pull-requests/) when you believe you have solved the problem. The solution will be evaluated and if valid, will be merged into the `master` branch.

