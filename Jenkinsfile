pipeline {
    agent none
    stages {
        stage('Configure (macOS)') {
            agent { label 'macos' }
            steps {
                sh "mkdir -p build"
                dir('build') {
                    sh "rm -rf Mackie\\ of\\ the\\ Unicorn.app Mackie_of_the_Unicorn.app Mackie-of-the-Unicorn-${GIT_VERSION}-*"
                    sh "/usr/local/bin/cmake -DCMAKE_BUILD_TYPE=Release .."
                }
            }
        }
        stage('Build (macOS)') {
            agent { label 'macos' }
            options { skipDefaultCheckout() }
            steps {
                dir('build') {
                    sh "/usr/bin/make -j4"
                }
            }
        }
        stage('Test (macOS)') {
            agent { label 'macos' }
            options { skipDefaultCheckout() }
            steps {
                dir('build') {
                    sh "./Unit_Tests --gtest_output=xml:./test-report.xml"
                }
                junit 'build/test-report.xml'
            }
        }
        stage('Package (macOS/docs)') {
            agent { label 'macos' }
            options { skipDefaultCheckout() }
            environment {
                GIT_VERSION = """${sh(
                    returnStdout: true,
                    script: 'git describe --always'
                ).trim()}"""
            }
            steps {
                dir('build') {
                    sh "rm -rf Mackie\\ of\\ the\\ Unicorn.app"
                    sh "mv Mackie_of_the_Unicorn.app Mackie\\ of\\ the\\ Unicorn.app"
                    sh "zip -r Mackie-of-the-Unicorn-${GIT_VERSION}-macOS.zip Mackie\\ of\\ the\\ Unicorn.app"
                    sh "mv doc/html Mackie-of-the-Unicorn-${GIT_VERSION}-docs"
                    sh "zip -r Mackie-of-the-Unicorn-${GIT_VERSION}-docs.zip Mackie-of-the-Unicorn-${GIT_VERSION}-docs"
                }
                archiveArtifacts artifacts: "build/Mackie-of-the-Unicorn-${GIT_VERSION}-macOS.zip"
                archiveArtifacts artifacts: "build/Mackie-of-the-Unicorn-${GIT_VERSION}-docs.zip"
            }
        }
        stage('Configure (Windows)') {
            agent { label 'windows' }
            steps {
                bat "set MKDIR_DIR=.\build && if not exist %MKDIR_DIR% mkdir %MKDIR_DIR%"
                dir('build') {
                    bat "cmake -DCMAKE_BUILD_TYPE=Release -G \"Visual Studio 17 2022\" .."
                }
            }
        }
        stage('Build (Windows)') {
            agent { label 'windows' }
            options { skipDefaultCheckout() }
            steps {
                dir('build') {
                    bat "MSBuild Mackie_of_the_Unicorn.sln /property:Configuration=Release -maxcpucount"
                }
            }
        }
        stage('Test (Windows)') {
            agent { label 'windows' }
            options { skipDefaultCheckout() }
            steps {
                dir('build') {
                    bat ".\\Release\\Unit_Tests.exe --gtest_output=xml:.\\test-report.xml"
                }
                junit 'build/test-report.xml'
            }
        }
        stage('Package (Windows)') {
            agent { label 'windows' }
            options { skipDefaultCheckout() }
            environment {
                GIT_VERSION = """${bat(
                    returnStdout: true,
                    script: '@git describe --always'
                ).trim()}"""
            }
            steps {
                dir('build') {
                    bat "move /y Release\\Mackie_of_the_Unicorn.exe \"Mackie of the Unicorn.exe\""
                    bat "tar -a -c -f Mackie-of-the-Unicorn-${GIT_VERSION}-Windows.zip \"Mackie of the Unicorn.exe\""
                }
                archiveArtifacts artifacts: "build/Mackie-of-the-Unicorn-${GIT_VERSION}-Windows.zip"
            }
        }
    }
}