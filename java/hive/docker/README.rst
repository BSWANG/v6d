Build Hive Docker Image with Hadoop
-----------------

### Prepare vineyard jars
```bash
    # Currently, the vineyard jar cannot run directly on hive because of
    # dependency conflicts. You can run it temporarily by reverting to an
    # older version of guava (such as 14.0.1) dependent by vineyard.
    # This problem will be fixed in the future.
    mvn clean package
```

### Build docker images
```bash
    cd v6d/java/hive/docker
    ./build.sh
```

### Create network
```bash
    docker network create hadoop-network
```

### Start sql server for hive metastore
```bash
    cd v6d/java/hive/docker/dependency/mysql
    docker-compose -f mysql-compose.yaml up -d
    # You can change the password in mysql-compose.yaml and hive-site.xml
```

### Run hadoop & hive docker images
```bash
    cd v6d/java/hive/docker
    docker-compose -f docker-compose-distributed.yaml up -d
```

### Prepare tez jars
```bash
    docker exet -it hive-metastore bash
    # in docker
    hdfs dfs -put /tez.tar.gz /
    exit
```

### Restart all services
```bash
    cd v6d/java/hive/distributed/docker
    docker-compose -f docker-compose.yaml restart
```

### Create table
```bash
    docker exec -it hive-hiveserver2 beeline -u "jdbc:hive2://hive-hiveserver2:10000" -n root
```

Using vineyard as storage
-----------------

### Run vineyardd
```bash
    cd v6d/build

    # at terminal 1
    ./bin/vineyardd --socket=~/vineyard_sock/0/vineyard.sock -rpc_socket_port=9601 --etcd_endpoint="0.0.0.0:2382"

    # at terminal 2
    ./bin/vineyardd --socket=~/vineyard_sock/1/vineyard.sock -rpc_socket_port=9602 --etcd_endpoint="0.0.0.0:2382"

    # at terminal 3
    ./bin/vineyardd --socket=~/vineyard_sock/2/vineyard.sock -rpc_socket_port=9603 --etcd_endpoint="0.0.0.0:2382"

    # at terminal 4
    ./bin/vineyardd --socket=~/vineyard_sock/metastore/vineyard.sock -rpc_socket_port=9604 --etcd_endpoint="0.0.0.0:2382"

    # at terminal 5
    ./bin/vineyardd --socket=~/vineyard_sock/hiveserver/vineyard.sock -rpc_socket_port=9605 --etcd_endpoint="0.0.0.0:2382"
```

### Copy vineyard jars to share dir
```bash
    mkdir -p ~/share
    cd v6d/java/hive
    # you can change share dir in docker-compose.yaml
    cp target/vineyard-hive-0.1-SNAPSHOT.jar ~/share
```

### Create table with vineyard
```bash
    docker exec -it hive-hiveserver2 beeline -u "jdbc:hive2://hive-hiveserver2:10000" -n root
```

```sql
    -- in beeline
    drop table test_vineyard;
    create table test_vineyard(field int);
    insert into table test_vineyard values (1),(2),(3),(4),(5),(6),(7),(8),(9),(10);
    select * from test_vineyard;
```