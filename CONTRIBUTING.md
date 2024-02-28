# Contributing to Raylib Bubbles

Feel free to contribute to the project if you have insights, improvements, bug fixes, or anything else!

### Creating an Issue

If you find inconsistencies, bugs, or other problems, consider creating an issue describing the problem.

**Note:** for comments, please use the *Discussions* tab instead!

### Gitflow Overview

We use the **Gitflow Workflow** for managing branches and pull requests. The main branches are:

+ **Main Branch:** Our production-ready state.
+ **Develop Branch:** Our primary development branch. All features are merged here before being released to the main branch.
+ **Feature Branches:** Branch off from `develop` when working on new features.

### Opening a Pull Request

+ *Fork* the repo.
+ *Clone* the forked repo to your local machine.
+ Checkout the `develop` branch: `git checkout develop`.
+ Update your local `develop` branch: `git pull origin develop`.
+ Create a new branch for your feature change: `git checkout -b feature/your_feature_name`. You can change `feature` to `bugfix` or `docsfix` if you are fixing a bug or a documentation error, respectively.
+ Make your changes and *commit* them: `git commit -m 'Added new feature'`.
+ *Push* the changes to your fork: `git push origin feature/your_feature_name`.
+ Create a *pull request* targeting the `develop` branch on the main repo.

### Code Style

| Rule | Description |
| ---- | ----------- |
| Brace Style | Use **K&R brace placement** for functions, classes, and control statements. |
| Indentation | Use **4 spaces** for indentation. Drop long initializer lists at one indent. |
| Naming Conventions | Use **`camelCase`** for variables and methods, and **`PascalCase`** for class names. |
| New Files | Use **LF line endings**, keep exactly one newline at the end of each file, use extension **`.hpp`** for C++ headers and **`.cpp`** for C++ source files. |
| Commenting | Short comments for complex logic are encouraged for public interfaces and significant private methods, using **`// NOTE:`** or **`// TODO:`** for important notes and tasks, but **please document the code in `README.md`** instead of in the code itself. |

### Non-Code Contributions

If you want to contribute backgrounds, sprites, audio or other assets, please **create an issue** to discuss the contribution! You are very welcome to contribute, but please make sure that the assets are **licensed under the MIT License** or a compatible license. If you are contributing assets you have created, please include a **`LICENSE`** file in the asset folder, stating you are the creator and that the assets are licensed under the MIT License or compatible.

### Testing and Reporting Bugs

If you find a bug, please **create an issue** describing the problem and how to reproduce it. If you have a fix, please **open a pull request**. As of now, testing is not enforced.

**Thank you!**
