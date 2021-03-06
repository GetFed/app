## set
GOOGLE_CLIENT_ID
GOOGLE_CLIENT_SECRET
get secret env file
`secret-config.env`

## Run commands:

```
eval "$(docker-machine env default)"
docker-machine start default

docker-compose build
docker-compose up
```

check volume directory in docker-compose.yml
volumes

docker-compose

## dev setup

steps are included here https://gist.github.com/kevin-smets/b91a34cea662d0c523968472a81788f7

### install kompose,minikube,docker,virtualbox

OSX
```
curl -L https://github.com/kubernetes/kompose/releases/download/v1.1.0/kompose-darwin-amd64 -o kompose
brew update && brew install kubectl && brew cask install docker minikube virtualbox
```

### verify

```
docker --version                # Docker version 17.09.0-ce, build afdb6d4
docker-compose --version        # docker-compose version 1.16.1, build 6d1ac21
docker-machine --version        # docker-machine version 0.12.2, build 9371605
minikube version                # minikube version: v0.22.3
kubectl version --client        # Client Version: version.Info{Major:"1", Minor:"8", GitVersion:"v1.8.1", GitCommit:"f38e43b221d08850172a9a4ea785a86a3ffa3b3a", GitTreeState:"clean", BuildDate:"2017-10-12T00:45:05Z", GoVersion:"go1.9.1", Compiler:"gc", Platform:"darwin/amd64"}      

```

### tagging docker repos

```
docker tag frontend gtdev87/tiro-frontend
docker push gtdev87/tiro-frontend
```

### Start Minikube

```
minikube start
```

### Check kubernetes

```
kubectl get nodes
```

### Use minikube's built-in docker daemon

```
eval $(minikube docker-env)
```

note revert is `eval $(docker-machine env -u)`

### Build, deploy and run an image on your local k8s setup crete local registry

Run docker locally to build the image (include steps later)

```
docker run -d -p 5000:31500 --restart=always --name registry registry:2
```

### run build and run kompose

```
kompose up
```

### port forwarding

```
kubectl get pods
kubectl port-forward <pod> 8080:3000
kubectl exec -it <pod> mix ecto.create
kubectl exec -it <pod> mix ecto.migrate
```

to find use localhost:8080

### local dashboard

```
minikube dashboard
```

### stop kube
```
kompose down
minikube stop
minikube destroy
```

## To deploy to prod from local comp

### instlall terraform for typhoon using the following steps

https://typhoon.psdn.io/cl/digital-ocean/


Add fingerprint to infra/clusters/terraform/providers.tf
```
ssh-keygen -E md5 -lf ~/.ssh/id_rsa.pub | awk '{print $2}'
```

`ssh_fingerprints = ["06:69:bc:6d:f6:fc:df:30:d7:ec:8a:2d:01:c6:35:6e"]`

### Add ssh agent

```
ssh-add ~/.ssh/id_rsa
ssh-add -L
```

```
cd infra/clusters/terraform/
terraform init
terraform plan
terraform apply
# this can take 10 mins
```

### To ssh into machne (optional)

```
ssh core@<machine-ip>
```

### setup kubernetes secret

```
export KUBECONFIG=/Users/GT/.secrets/clusters/tiro/auth/kubeconfig
```

### setup cluster

it may make sense to initially start with non existant volume

if so delete volume from digitalocean

```
cd ../kubernetes
kubectl create -f ./secret.yml
kubectl apply -f https://raw.githubusercontent.com/digitalocean/csi-digitalocean/master/deploy/kubernetes/releases/csi-digitalocean-v0.2.0.yaml
```

### clean repos
```
make clean
```

### Start up Boot2Dock

```
docker-machine create --driver virtualbox --virtualbox-disk-size "400000" default
```
or 
```
# if already created
make clean # clean folders
docker-machine restart default

# worst case
docker-machine rm default
docker-machine create --driver virtualbox --virtualbox-disk-size "400000" default

# restart laptop and do ^ super worst case
```

### Test and setup with

```
docker-machine env default
eval "$(docker-machine env default)"
```

### Docker registry dockerhub



```

cd ../../../ # root
kompose up --verbose
```

if pv doesn't spawn.  create volume manually on digital ocean


### See kubernetes cluster

```
kubectl get deployment,svc,pods,pvc
```

### expose app
```
kubectl create -R -f infra/clusters/kubernetes/typhoon/addons/nginx-ingress/digital-ocean/
kubectl create -f infra/clusters/kubernetes/staging-ingress-setup.yaml

``` 

### create domains for
```
tiro-workers.dubcell.com
api.tiro-workers.dubcell.com
auth.tiro-workers.dubcell.com
```