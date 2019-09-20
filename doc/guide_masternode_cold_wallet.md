
# Single masternode on Linux VPS + cold control wallet on local PC
------
This guide is for a single masternode, on a Ubuntu 16.04 64bit server(1GB RAM) and will be controlled from the wallet on your local computer.

First the basic requirements:
* 1000 DEXR (https://wallet.crypto-bridge.org/market/BRIDGE.DEXR_BRIDGE.BTC)
* A main computer (Your everyday computer) – This will run the control wallet, hold your collateral 1000 Dexergi and can be turned on and off without affecting the masternode.
* Masternode Server(VPS - The computer that will be on 24/7)
* A unique IP address for EACH masternode

The basic reasoning for these requirements is that, you get to keep your DEXR in your local wallet, and host your masternode remotely, securely.

For this guide, I’m going to refer to your main computer’s wallet as the main wallet, and the masternode wallet as the masternode wallet.

-------

### I. Deploy masternode VPS

1. Get a VPS server with min. 1GB RAM and Ubuntu 16.04 as operating system
2. RUN script bellow:
   ```wget -qO- https://raw.githubusercontent.com/dexergiproject/dxr-mn-scripts/master/vps-setup.sh | bash```
    
   (It may take 2-3 minutes. It will automatically install and configure masternode wallet for your masternode server!)

### II. Installing control wallet

1. Go to https://dexergi.io/ and download wallet for your Operating system.
2. Unpack it and launch ***dexergi-qt.exe*** or appropriate binaries for your control wallet. We have it for all, WINDOWS / MAC / LINUX.
3. Select "Use a custom data directory" or "Use defualt data directory" as per your convineance.



## Configuration

**Note**: The auto minter should be disabled during this setup to prevent autominting of your masternode collateral. BEFORE unlocking your wallet, you can disable autominting in the control wallet option menu.

1. Using the control wallet, enter the debug console (Tools > Debug console) and type the following command:
```createmasternodekey``` (This will be the masternode’s privkey. We’ll use this later…)

2. Using the control wallet still, enter the following command:
```getaccountaddress chooseAnyNameForYourMasternode```

3. Still in the control wallet, send 1000 DEXERGI to the address you generated in step 2 (Be 100% sure that you entered the address correctly. You can verify this when you paste the address into the “Pay To:” field, the label will autopopulate with the name you chose”, also make sure this is exactly 1000 DEXERGI; No less, no more.)
– Be absolutely 100% sure that this is copied correctly. And then check it again. We cannot help you, if you send 1000 DEXERGI to an incorrect address.

4. Still in the control wallet, enter the command into the console:
```getmasternodeoutputs``` (This gets the proof of transaction of sending 1000)

5. Still on the main computer, go into the DEXERGI data directory, by default in Windows it’ll be %Appdata%/DEXERGI or ~ for LINUX
Find masternode.conf and add the following line to it:

```<Name of Masternode(Use the name you entered earlier for simplicity)> <Unique IP address>:5536 <The result of Step 1> <Result of Step 4> <The number after the long line in Step 4>```

Example: MN1 31.14.135.27:5536 892WPpkqbr7sr6Si4fdsfssjjapuFzAXwETCrpPJubnrmU6aKzh c8f4965ea57a68d0e6dd384324dfd28cfbe0c801015b973e7331db8ce018716999 1

Substitute it with your own values and without the “<>”s

**VPS Remote wallet install**

6. Install the latest version of the DEXERGI wallet onto your masternode.

**Note**: If this is the first time running the wallet in the VPS, you’ll need to attempt to start the wallet `./dexergid` this will place the config files in your ~/.dexergi data directory. Press CTRL+C to exit / stop the wallet then continue to step  7.

**Configuration Continuation**

7. Now on the masternodes, find the dexergi data directory here.(Linux: ~/.dexergi)cd ~/.dexergi

8. Open the dexergi.conf by typing `vi dexergi.conf` then press i to go into insert mode and make the config look like this:
```
rpcuser=<long_random_username>
rpcpassword=longer random password
rpcallowip=127.0.0.1
server=1
daemon=1
listen=1
masternode=1
masternodeaddr=IP:5536 (same as configured in masternode.conf) 
masternodeprivkey=Result of Step 1
```

*Make sure to replace rpcuser and rpcpassword with your own.*

9. To exit the editor press esc then :wq! then press enter
Start your masternode

10. Now, you need to finally start these things in this order
    1. Start the daemon client in the VPS. Start the wallet using `./dexergid`
    
    2. From the Control wallet debug console startmasternode alias false <mymnalias>
    where <mymnalias> is the name of your masternode alias (without brackets)
    The following should appear:
   
    ```
    “overall” : “Successfully started 1 masternodes, failed to start 0, total 1”,
    “detail” : [
    {
    “alias” : “<mymnalias>”,
    “result” : “successful”,
    “error” : “”
    } 
    ```
   
    3. Back in the VPS (remote wallet), start the masternode./dexergi-cli startmasternode local false
    
    4. A message “masternode successfully started” should appear
   
11. Use the following command to check status on VPS:
`./dexergi-cli getmasternodestatus`
You should see something like:

```
{
“txhash” : “334545645643534534324238908f36ff4456454dfffff51311”,
“outputidx” : 0,
“netaddr” : “45.11.111.111:5536”,
“addr” : “D6fujc45645645445645R7TiCwexx1LA1”,
“status” : 4,
“message” : “Masternode successfully started”
}
```
   
**Debugging**:

* If after following these steps exactly, you still get “Not capable masternode: Could not connect to 139.99.204.152:5536”, ensure that new blocks are being generated in the blockchain

* If, while starting on the vps you get the error “Not capable masternode: Hot node, waiting for remote activation.”, keep on retrying. It can take up to 30 minutes to work.
   
#### *Congratulations! You have successfully created your masternode!*
