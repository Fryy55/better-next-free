# Better "Next Free"
###### requested by [CarlIsBored](user:10748478)

This mod completely reimplements "Next Free" buttons to fix vanilla problems with them

### <cd>Groups</c>
Normally, the editor counts stuff like triggers that target <cc>Control IDs</c> or the target item of <cl>Item Edit Triggers</c> towards the Next Free group, and doesn't count stuff like <cp>Move Trigger</c>'s center group. Now **all** your groups will be calculated properly

#### **<cf>Fixed objects:</c>**
- Move Trigger
- Stop Trigger
- Rotate Trigger
- Keyframe Animation Trigger
- Edit Advanced Follow Trigger
- Re-Target Advanced Follow Trigger
- Edit Area Triggers
- Area Stop Trigger
- Item Edit Trigger
- Advanced Random Trigger
- Sequence Trigger
- Gradient Trigger
- Checkpoint
- ALL collectibles (Keys, Hearts, Clocks, Pixel objects...)

### <cc>Colors</c>, <cp>Effect IDs</c>, <cb>Block IDs</c>, <cg>Editor Layers</c>, <cs>Enter Channels</c>, <c-293F84>G</c><c-2C4B7D>r</c><c-2F5675>a</c><c-33626F>d</c><c-366C69>i</c><c-397662>e</c><c-3B7F5D>n</c><c-3D8857>t</c> <c-409052>I</c><c-42984D>D</c><c-45A048>s</c>, <co>Item IDs</c>, <ca>Order Channels</c>, <cf>SFX IDs</c> and <cl>SFX Groups</c>
All those functions normally count the current input field towards used IDs, which makes clicking them twice confusing due to IDs changing back and forth. Now they behave similar to <cd>groups</c> - clicking "Next Free" multiple times will <cf>not</c> increment the ID, making the next free ID more obvious

## Support and feedback
You can leave your feedback in the Issues tab or by joining my [Discord server](https://discord.com/invite/4vqtjfdhTk)

## License
This project is distributed under the **Apache-2.0 License**.

See `LICENSE` for permissions, conditions and limitations.