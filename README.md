# Computer Hardware Store Inventory

Command-line inventory manager for hardware components.

## Build
```sh
make
```

## Run
```sh
./bin/inventory help
```

## Usage

View all available commands:
```sh
./bin/inventory help
```

Basic examples:
```sh
# List items
./bin/inventory list-products
./bin/inventory list-manufacturers
./bin/inventory list-categories

# Search and filter
./bin/inventory search-model --substr "RTX"
./bin/inventory list-below --threshold 20
./bin/inventory sort-products --by price

# Add items (returns UUID)
./bin/inventory add-manufacturer --name "NVIDIA" --country "USA" --est-month 4 --est-year 1993 --website "https://nvidia.com" --warranty 36
./bin/inventory add-category --name "GPUs" --desc "Graphics cards"
./bin/inventory add-product --model "RTX 4080" --man <UUID> --cat <UUID> --sku "RTX4080" --price 999.99 --stock 50 --rel-month 1 --rel-year 2024 --score 9500 --power 320 --iface "PCIe 4.0" --warranty 36

# Update and delete
./bin/inventory upd-stock --uuid <UUID> --stock 25
./bin/inventory upd-price --uuid <UUID> --price 899.99
./bin/inventory del-product --uuid <UUID>
```
