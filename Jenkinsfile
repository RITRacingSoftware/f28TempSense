pipeline {
    agent { docker { image 'f28ts' } }
    stages {
        stage('build') {
            steps {
                sh 'make'
            }
        }
    }
}